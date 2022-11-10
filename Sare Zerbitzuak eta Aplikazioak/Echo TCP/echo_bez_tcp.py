#!/usr/bin/env python3

import socket, sys

PORT = 50007

# Egiaztatu argumentu bat pasa dela.
if len(sys.argv) != 2:
	print("Erabilera: {} <zerbitzaria>".format(sys.argv[0]))
	exit(1)

zerb_helb = (sys.argv[1], PORT)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(zerb_helb)

print("Sartu bidali nahi duzun mezua (hutsa bukatzeko):")
while True:
	mezua = input()
	if not mezua:
		break
	
	mezua_ = mezua.encode('UTF-8')
	s.sendall(mezua_)
	
	jasotako_byteak = 0
	erantzuna = b''
	while jasotako_byteak < len(mezua_):
		jasotako_mezua = s.recv(1024)
		erantzuna += jasotako_mezua
		jasotako_byteak += len(jasotako_mezua)
  
	print(erantzuna.decode('UTF-8'))
s.close()