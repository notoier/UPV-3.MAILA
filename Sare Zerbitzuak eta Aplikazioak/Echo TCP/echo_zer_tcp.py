#!/usr/bin/env python3

import socket

PORT = 50007

"""IKASLEAK BETETZEKO:
Sortu socket bat, esleitu helbide bat eta ezarri entzute socket
bezala.
"""
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('', PORT))
s.listen(5)



while True:
	elkarrizketa, _ = s.accept()
	while elkarrizketa:
 		elkarrizketa.sendall(elkarrizketa.recv())
s.close()
