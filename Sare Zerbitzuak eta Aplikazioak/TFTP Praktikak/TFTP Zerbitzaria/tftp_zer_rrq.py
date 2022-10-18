#!/usr/bin/env python3

import sys
import os
import socket

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

	data = f.read(BLOCK_SIZE)
	block_num = 1
 
	DATAMSG = DATA + int.to_bytes(block_num, 2, 'big') + data 
	s.sendto(DATAMSG, addr)
 
	last = False if len(data) == BLOCK_SIZE else True
	while True:  
		mezua, helb =	s.recvfrom(516)
		opcode = mezua[0:2]
		actual_block = mezua[2:4]
		
		if helb != addr: #Jasotako helbidea desberdina bada, orduan baztertu mezua
			continue

		if opcode == ERROR: #Errore kodea bada, orduan errorrea pantailaratu
			print('ERROR CODE:' + actual_block.decode('ascii'))
			print(mezua[4:len(mezua) - 1 ].decode('ascii'))
			exit(1)
   
		if opcode != ACK:
			continue

		if block_num != int.from_bytes(actual_block):
			continue
		
		if last:
			break

		block_num += 1
		data = f.read(BLOCK_SIZE)
		DATAMSG = DATA + int.to_bytes(block_num) + data
		s.sendto(DATAMSG, addr)
  
		if len(data) < BLOCK_SIZE:
			last = True

	f.close()
 
def write_file(s, addr, filename):
	f = open(FILES_PATH + filename, 'w')
	block_num = 0
	last = False
	while True:
		s.sendto(ACK + int.to_bytes(block_num, 2, 'big'), addr)
		mezua = s.recv(516)
		opcode = mezua[0:2]
		if opcode == ERROR:
			exit(1)
		elif opcode != DATA:
			continue
		else:
			actual_block = mezua[2:4]
			data = mezua[4:].decode('UTF-8')
			block_num += 1
			if actual_block != block_num:
				continue
			if last:
				break
			
  
if __name__ == '__main__':
	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	s.bind(('0.0.0.0', PORT))

	while True:
		req, cli_addr = s.recvfrom(64)
		
		opcode = req[:2]
		if opcode != RRQ or opcode != WRQ:
			send_error(s, cli_addr, 5, 'Unexpected opcode.')
		else:
			filename, mode, _ = req[2:].split(b'\x00')
			if mode.decode().lower() not in ('octet', 'binary'):
				send_error(s, cli_addr, 0, 'Mode unkown or not implemented')
				continue
		filename = os.path.basename(filename.decode()) # For security, filter possible paths.
		if opcode == RRQ:
			send_file(s, cli_addr, filename)
		else:
			write_file(s, cli_addr, filename)
