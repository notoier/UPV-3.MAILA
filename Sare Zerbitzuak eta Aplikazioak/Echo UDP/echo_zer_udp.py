#!/usr/bin/env python3

import socket, sys

PORT = 50007 # 4. ARIKETA GEHIGARRITIK AURRERA EZ DA BEHARREZKOA

# ARIKETA GEHIGARRIA 4
if len( sys.argv ) != 2:
	print( "Erabilera: {} <portua>".format( sys.argv[0] ) )
	exit( 1 )

PORT_BERRIA = int(sys.argv[1])

"""IKASLEAK BETETZEKO:
Sortu socketa eta esleitu helbide bat.
"""
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('',PORT_BERRIA))

while True:
	"""IKASLEAK BETETZEKO:
	Jaso mezu bat eta erantzun datu berdinekin.
	"""
	echo, bez_helb = s.recvfrom(1024)
	s.sendto(echo, bez_helb)

"""IKASLEAK BETETZEKO:
Itxi socketa.
"""
s.close()

