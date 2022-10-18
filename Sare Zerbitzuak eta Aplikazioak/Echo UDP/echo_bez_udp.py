#!/usr/bin/env python3

import socket, sys

PORT = 50007

# 5. ARIKETA GEHIGARRITIK AURRERA EZ DA BEHARREZKOA
# Egiaztatu argumentu bat pasa dela.
# if len( sys.argv ) != 2:
# 	print( "Erabilera: {} <zerbitzaria>".format( sys.argv[0] ) )
# 	exit( 1 )

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


while True:
	# ARIKETA GEHIGARRIA 5
	# Zerbitzariaren domeinua eskatu
	print("Sartu mezua bidali nahi diozun zerbitzariaren domeinua: ")
 
	while True:
		domeinua = input()
		if domeinua:
			break
		print("Ez da zerbitzari domeinu egokia sartu!\n Sartu mezua bidali nahi diozun zerbitzariaren domeinua: ")
	zerb_helb = (domeinua, PORT)
	
	print("Sartu bidali nahi duzun mezua (hutsa bukatzeko):")
	mezua = input()
	if not mezua:
		break

	mezua_byte = mezua.encode('utf-8')
	s.sendto(mezua_byte, zerb_helb)
	buf = s.recv(1024)
	print("------------------------------------------")
	jasotako_mezua = buf.decode('utf-8')
	print(jasotako_mezua)
	# ARIKETA GEHIGARRIA 1
	print(f"Bidalitako mezuaren luzeera -> String: {len(mezua)}, Byte: {len(mezua_byte)}\nJasotako mezuaren luzeera -> String: {len(jasotako_mezua)}, Byte: {len(buf)}")
	# ARIKETA GEHIGARRIA 2
	print(f"Iturburua -> IP: {zerb_helb[0]} Portua: {zerb_helb[1]}")
	# ARIKETA GEHIGARRIA 3
	bezero_socket_info = s.getsockname()
	print(f"Bezeroa -> IP: {bezero_socket_info[0]}, Portua: {bezero_socket_info[1]}")

s.close()

