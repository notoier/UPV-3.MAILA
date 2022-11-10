#!/usr/bin/env python3

import socket

PORT = 50007

"""IKASLEAK BETETZEKO:
Sortu socket bat, esleitu helbide bat eta ezarri entzute socket
bezala.
"""
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', PORT))
s.listen(5)



while True:
	elkarrizketa, _ = s.accept()
	buf_mezua=  elkarrizketa.recv(1024)
	while buf_mezua:
		elkarrizketa.sendall(buf_mezua)
		buf_mezua = elkarrizketa.recv(1024)
   
s.close()