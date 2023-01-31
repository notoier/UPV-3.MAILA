#!/usr/bin/env python3

import socket, sys, time
import getpass
import ssl

ZERB_POP = "ikasle.ehu.eus"
PORT_POP = 995
ZERB_SMTP = "smtp.ehu.eus"
PORT_SMTP = 25

def recvline(s, removeEOL = True):
	"""s socketetik irakurtzen du lerro jauzi bat (CRLF) jaso arte"""
	line = b''
	CRreceived = False
	while True:
		c = s.recv(1)
		if c == b'':
			raise EOFError("Connection closed by the peer before receiving an EOL.")
		line += c
		if c == b'\r':
			CRreceived = True
		elif c == b'\n' and CRreceived:
			if removeEOL:
				return line[:-2]
			else:
				return line
		else:
			CRreceived = False

def isPOPerror(msg):
	if msg.startswith("-ERR"):
		print("POP3 errorea! {}".format(msg[5:]))
	return msg.startswith("-ERR")

def isSMTPerror(msg, OKcode):
	code = str(OKcode)
	if not msg.startswith(code):
		print("SMTP errorea! {}".format(msg[len(code)+1:]))
	return not msg.startswith(code)

def int2bytes( n ):
	if n < 1 << 10:
		return str(n) + " B  "
	elif n < 1 << 20:
		return str(round( n / (1 << 10) ) ) + " KiB"
	elif n < 1 << 30:
		return str(round( n / (1 << 20) ) ) + " MiB"
	else:
		return str(round( n / (1 << 30) ) ) + " GiB"

if __name__ == "__main__":
#####################################
# Aztertu zure buzoia POP3 erabiliz
#####################################
	helb_pop = (ZERB_POP, PORT_POP)
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	context = ssl.create_default_context()
	ss = context.wrap_socket(s, server_hostname = ZERB_POP)
	ss.connect(helb_pop)

	msg = recvline(ss).decode("ascii")
	if isPOPerror(msg):
		exit(1)

	ziurt_pop = ss.getpeercert()
	print("POP3 zerbitzariaren ziurtagiria:")
	print(ziurt_pop)
	try:
		ssl.match_hostname(ziurt_pop, ZERB_POP)
	except Exception as e:
		print("Error: {}".format(e))
		exit(1)
	else:
		print("'{}' izena POP3 zerbitzariaren ziurtagirian egiaztatua!".format(ZERB_POP))

	erab = input('Zein da zure buzoiaren erabiltzaile izena? ')
	msg = "USER {}\r\n".format(erab)
	ss.sendall(msg.encode("ascii"))
	msg = recvline(ss).decode("ascii")
	if isPOPerror(msg):
		exit(1)

	pasahitza = getpass.getpass('Zein da pasahitza?')
	msg = "PASS {}\r\n".format(pasahitza)
	ss.sendall(msg.encode("ascii"))
	msg = recvline(ss).decode("ascii")
	if isPOPerror(msg):
		exit(1)
	print("Erabiltzailea ondo kautotu da POP3 zerbitzarian.")

	msg = "STAT\r\n"
	ss.sendall(msg.encode("ascii"))
	msg = recvline(ss).decode("ascii")
	if isPOPerror(msg):
		exit(1)
	tokens = msg.split()
	print('Mezu kopurua: {}, Buzoiaren tamaina: {}'.format(tokens[1], int2bytes(int(tokens[2]))))
	mezuak_guztira = int(tokens[1])

	irakasgaiak = ['SZA_22-23', 'SAR_2022-23']
	zenbat_mezu = dict()
	for irakasgaia in irakasgaiak:
		zenbat_mezu[irakasgaia] = 0
	for i in range(mezuak_guztira):
		msg = "TOP {} 0\r\n".format(i + 1)
		ss.sendall(msg.encode("ascii"))
		msg = recvline(ss).decode("ascii")
		if isPOPerror(msg):
			exit(1)
		while True:
			lerroa = recvline(ss).decode("ascii")
			if lerroa == ".":
				break
			if lerroa.startswith("Subject:"):
				for irakasgaia in irakasgaiak:
					if irakasgaia + ":" in lerroa:
						zenbat_mezu[irakasgaia] += 1
						break
	for irakasgaia, zenbat in zenbat_mezu.items():
		print("{}: {}".format(irakasgaia, zenbat))

	msg = "QUIT\r\n"
	ss.sendall(msg.encode("ascii"))
	msg = recvline(ss).decode("ascii")
	if isPOPerror( msg ):
		exit( 1 )
	ss.close()

#############################
# Bidali mezua SMTP erabiliz
#############################
	helb_smtp = (ZERB_SMTP, PORT_SMTP)
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect(helb_smtp)
	msg = recvline(s).decode("ascii")
	if isSMTPerror(msg, 220):
		exit(1)

	msg = "EHLO bezeroa.sza\r\n"
	s.sendall(msg.encode("ascii"))
	msg = recvline(s).decode("ascii")
	if isSMTPerror(msg, 250):
		exit(1)
	starttls_onartua = False
	while True:
		msg = recvline(s).decode("ascii")
		if isSMTPerror(msg, 250):
			exit(1)
		if msg[4:].startswith("STARTTLS"):
			starttls_onartua = True
		if msg[3] == " ":
			break
	if not starttls_onartua:
		print("Zerbitzariak ez du STARTTLS onartzen.")
		exit(1)
	msg = "STARTTLS\r\n"
	s.sendall(msg.encode("ascii"))
	msg = recvline(s).decode("ascii")
	if isSMTPerror(msg, 220):
		exit(1)
	context = ssl.create_default_context()
	ss = context.wrap_socket(s, server_hostname = ZERB_SMTP)
	ziurt_smtp = ss.getpeercert()
	print("SMTP zerbitzariaren ziurtagiria:")
	print(ziurt_smtp)
	try:
		ssl.match_hostname(ziurt_smtp, ZERB_SMTP)
	except Exception as e:
		print("Error: {}".format(e))
		exit(1)
	else:
		print("'{}' izena SMTP zerbitzariaren ziurtagirian egiaztatua!".format(ZERB_SMTP))
	msg = "EHLO bezeroa.sza\r\n"
	ss.sendall(msg.encode("ascii"))
	msg = recvline(ss).decode("ascii")
	if isSMTPerror(msg, 250):
		exit(1)
	while True:
		msg = recvline(ss).decode("ascii")
		if isSMTPerror(msg, 250):
			exit(1)
		if msg[3] == " ":
			break
	
	nork = "ni@sza.eus"
	nori = "zu@ikasle.ehu.eus"
	mezua = "From: Ni neu <{}>\r\n".format(nork)
	mezua += "To: Zu zeu <{}>\r\n".format(nori)
	mezua += "Subject: SZA prakitkako bilaketaren emaitza\r\n"
	mezua += "Date: " + time.ctime() + "\r\n"
	mezua += "\r\n"
	mezua += "eGela ikastaro bakoitzeko mezu kopurua\r\n"
	mezua += "--------------------------------------\r\n"
	for irakasgaia, zenbat in zenbat_mezu.items():
		mezua += "{}: {}\r\n".format(irakasgaia, zenbat)

	msg = "MAIL From: {}\r\n".format(nork)
	ss.sendall(msg.encode("ascii"))
	msg = recvline(ss).decode("ascii")
	if isSMTPerror(msg, 250):
		exit(1)
	msg = "RCPT to: {}\r\n".format(nori)
	ss.sendall(msg.encode("ascii"))
	msg = recvline(ss).decode("ascii")
	if isSMTPerror(msg, 250):
		exit(1)
	msg = "DATA\r\n"
	ss.sendall(msg.encode("ascii"))
	msg = recvline(ss).decode("ascii")
	if isSMTPerror(msg, 354):
		exit(1)
	ss.sendall(mezua.encode("ascii"))
	ss.sendall("\r\n.\r\n".encode("ascii"))
	msg = recvline(ss).decode("ascii")
	if isSMTPerror(msg, 250):
		exit(1)
	print("Mezua ondo bidali da.")
	msg = "QUIT\r\n"
	ss.sendall(msg.encode("ascii"))
	msg = recvline(ss).decode("ascii")
	if isSMTPerror(msg, 221):
		exit(1)
	ss.close()

