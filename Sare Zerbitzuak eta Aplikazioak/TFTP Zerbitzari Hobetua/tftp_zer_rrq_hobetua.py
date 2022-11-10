#!/usr/bin/env python3

import sys
import os
import socket
import signal
import select

NULL  = b'\x00'
RRQ   = b'\x00\x01'
WRQ   = b'\x00\x02'
DATA  = b'\x00\x03'
ACK   = b'\x00\x04'
ERROR = b'\x00\x05'

PORT = 50069
BLOCK_SIZE = 512
FILES_PATH ='./data/'

def send_error(s, addr, code, message):
	resp  = ERROR
	resp += code.to_bytes(2, 'big')
	resp += message.encode()
	resp += NULL
	s.sendto(resp, addr)
	
def send_file(s, addr, filename):
	try:
		f = open(os.path.join(FILES_PATH, filename), 'rb')
	except:
		send_error(s, addr, 1, 'File not found.')
		exit(1)

	"""IKASLEAK BETETZEKO: [Enuntziatuko 5. pausoa]
	"Konektatu" socketa bezeroarekin.
	Erabili send funtzioa sendto funtzioaren ordez prozesu umean.
	Erabili recv funtzioa recvfrom funtzioaren ordez prozesu umean.
	"""
 
	data = f.read(BLOCK_SIZE)
	resp  = DATA
	resp += b'\x00\x01'
	resp += data
	s.sendto(resp, addr)

	block_num = 1
	last = False if len(data) == BLOCK_SIZE else True
	while True:
		s_, _, _ = select.select([s],[],[], 0.5)
		if not s_:
			err += 1
			if err <= 3:
				break
			s.sendto(resp, addr)
			continue
		err = 0
		s = s_[0]
		resp, cli_addr = s.recvfrom(64)
		opcode = resp[:2]
		if opcode == ERROR:
			error_code = int.from_bytes(resp[2:4], 'big')
			print('Server error {}: {}'.format(error_code, resp[4:-1].decode()))
			exit(1)
		elif opcode != ACK:
			print('Unexpected response.')
			exit(1)
		else:
			ack_num = int.from_bytes(resp[2:4], 'big')
			if ack_num != block_num:
				continue
			if last:
				break

			block_num = (block_num + 1) if block_num % 2^16 != 0 else 0
			data = f.read(BLOCK_SIZE)
			resp  = DATA
			resp += block_num.to_bytes(2, 'big')
			resp += data
			s.sendto(resp, addr)
			if len(data) < BLOCK_SIZE:
				last = True
			

	print('{}: {} bytes sent.'.format(filename, (block_num - 1) * BLOCK_SIZE + len(data)))
	f.close()

if __name__ == '__main__':
    
	signal.signal(signal.SIGCHLD, signal.SIG_IGN)
	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	s.bind(('', PORT))

	while True:
		req, cli_addr = s.recvfrom(64)
		
		if os.fork():
			pass

		else:
			su = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
			s.close()
			opcode = req[:2]
			if opcode != RRQ:
				send_error(s, cli_addr, 5, 'Unexpected opcode.')
			else:
				filename, mode, _ = req[2:].split(b'\x00')
				if mode.decode().lower() not in ('octet', 'binary'):
					send_error(s, cli_addr, 0, 'Mode unkown or not implemented')
					continue
			filename = os.path.basename(filename.decode()) # For security, filter possible paths.
			send_file(s, cli_addr, filename)
			su.close()
			exit(1)
	s.close()