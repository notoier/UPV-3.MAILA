#!/usr/bin/env python3

from cmath import exp
import sys
import socket
import time

NULL  = b'\x00'
RRQ   = b'\x00\x01'
WRQ   = b'\x00\x02'
DATA  = b'\x00\x03'
ACK   = b'\x00\x04'
ERROR = b'\x00\x05'

PORT = 50069
BLOCK_SIZE = 512

def get_file(s, serv_addr, filename):
	
	start = time.time()

	f = open(filename, 'wb')

	eskaera = RRQ + filename.encode('ascii') + NULL + "octet".encode('ascii') + NULL
	s.sendto(eskaera, serv_addr)
	expected_block = 1
	while True:
		data =  b''
		buf, zerb_helb = s.recvfrom(516)
		opcode = buf[0:2]
		if opcode != DATA:
			break
		
		actual_block = int.from_bytes(buf[2:3])
		if expected_block != actual_block:
			data = buf[4:]
			f.write(data)
			s.sendto(ACK + buf[2:4], zerb_helb)
			if len(buf[4:]) <= BLOCK_SIZE:
				break
			expected_block += 1
   
	f.close()
	elapsed = time.time() - start
	bytes_received = (expected_block - 1) * BLOCK_SIZE + len(data)
	print('{} bytes received in {:.2e} seconds ({:.2e} b/s).'.format(bytes_received, elapsed, bytes_received * 8 / elapsed))

if __name__ == '__main__':
	if len(sys.argv) != 3:
		print('Usage: {} server filename'.format(sys.argv[0]))
		exit(1)

	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	serv_addr = (sys.argv[1], PORT)

	get_file(s, serv_addr, sys.argv[2])
