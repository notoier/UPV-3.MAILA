#!/usr/bin/env python3

import socket, sys, ssl
import getpass
import smtplib

# Zehaztu POP zerbitzariaren izena/helbidea eta portua
ZERB_POP = '158.227.125.103'
PORT_POP = 110

# Zehaztu SMTP zerbitzariaren izena/helbidea eta portua
ZERB_SMTP = '158.227.125.103'
PORT_SMTP = 587

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

if __name__ == "__main__":
	#####################################
	# Aztertu zure buzoia POP3 erabiliz
	#####################################
	helb_pop = (ZERB_POP, PORT_POP)
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	"""IKASLEAK BETETZEKO:
	POP3 zerbitzariarekin konexio segurua ezarri (TLS inplizitua).
	Pantailaratu eta egiaztatu zerbitzariaren ziurtagiria.
	"""
	
#	context = ssl.create_default_context()
#	ss = context.wrap_socket(s, server_hostname=ZERB_POP)
	s.connect(helb_pop)
	recvline(s)

#	cert = s.getpeercert()
#	print(cert)

#	ssl.match_hostname(cert, ZERB_POP)

	"""IKASLEAK BETETZEKO:
	AUTHORIZATION fasea (erabiltzailea kautotu).
	"""

	while True:
		erab = input('Zein da zure buzoiaren erabiltzaile izena? ')
		
		s.send(('USER ' + erab + '\r\n').encode('ASCII'))
		recvline(s)

		pasahitza = getpass.getpass('Zein da pasahitza?')

		s.send(('PASS ' + pasahitza + '\r\n').encode('ASCII'))
		resp = recvline(s).decode('ascii')

		if resp == '+OK':
			break
		else:
			print("Pasahitza edo erabiltzailea txarto dago!")

	"""IKASLEAK BETETZEKO:
	TRANSACTION fasea (mezuak aztertu).
	"""

	sza2223 = 0

	s.send('STAT\r\n'.encode('ascii'))
	resp = recvline(s).decode('ascii')
	mail_count = resp.split(' ')[1]
	for i in  range(int(mail_count)):
		s.send(('TOP ' + str(i+1) + ' 0\r\n').encode('ascii'))
		resp = ""
		while True:
			line = recvline(s).decode('ascii')
			if line == '.':
				break
			resp += line + '\n'

		print(resp)
		subject = resp.splitlines()[6][9:18]
		if subject == 'SZA_22-23':
			sza2223 += 1

	if sza2223 == 1:
		print("Guztira gai bezala 'SZA_22-23' hasieran duen mezu bakarra dago.")
	else:
		print("Guztira gai bezala 'SZA_22-23' hasieran duten " + str(sza2223) + " mezu daude.")


	"""IKASLEAK BETETZEKO:
	UPDATE fasea (POP3 saioa itxi).
	Itxi TLS saioa.
	"""

	s.send(('QUIT\r\n').encode('ascii'))
#	resp = recvline(s).decode('ascii')
#	if resp != '+OK':
#		print(resp)
	

#############################
# Bidali mezua SMTP erabiliz
#############################
	"""IKASLEAK BETETZEKO:
	Session Initiation (konektatu SMTP zerbitzarira eta jaso ongietorri mezua).
	"""
	helb_smtp = (ZERB_SMTP, PORT_SMTP)
	s = smtplib.SMTP(helb_smtp[0], helb_smtp[1])
	

	"""IKASLEAK BETETZEKO:
	Client Initiation (zerbitzaria agurtu).
	Nahi baduzu, SMTP zerbitzariarekin konexio segurua ezarri (STARTTLS). Kasu horretan, pantailaratu eta egiaztatu zerbitzariaren ziurtagiria.
	"""

	s.ehlo()
	user = input("Erabiltzailea: ")
	password = getpass.getpass("Pasahitza: ")
	s.login(user, password)

	"""IKASLEAK BETETZEKO:
	Bidali beharreko mezua osatu (goiburua eta gorputza).
	"""

	msg = f"From: {user} <{user}@sza.sar>\nTo: Oier <oalvarez017@ikasle.ehu.eus>\nSubject: SZA mezu kopurua\n\nSZA mezu kopurua {sza2223}-koa da.\r\n"

	"""IKASLEAK BETETZEKO:
	Mail Transactions (mezua bidali).
	"""

	s.sendmail(f'{user}@sza.sar', 'oalvarez017@ikasle.ehu.eus', msg)

	"""IKASLEAK BETETZEKO:
	Terminating Sessions and Connections (SMTP saioa itxi).
	Konexioa itxi.
	"""

	s.quit()
