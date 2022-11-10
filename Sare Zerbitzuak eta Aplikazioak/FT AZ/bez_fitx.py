#!/usr/bin/env python3

import socket, sys, os
import szasar

SERVER = 'localhost'
PORT = 6012
ER_MSG = (
	"Dena ondo. Errorerik ez.",
	"Komando ezezaguna edo ustegabekoa.",
	"Erabiltzaile ezezaguna.",
	"Pasahitz okerra.",
	"Arazoa fitxategi zerrenda sortzen.",
	"Fitxategia ez da existizen.",
	"Arazoa fitxategia jaistean.",
	"Erabiltzaile anonimoak ez dauka honetarako baimenik.",
	"Arazoa fitxategia ezabatzean." )

class Menua:
	List, Download, Upload, Delete, Exit = range( 1, 6 )
	Options = ( "Fitxategi zerrenda", "Fitxategia jaitsi", "Fitxategia igo", "Fitxategia ezabatu", "Saioa amaitu" )

	def menua():
		print( "+{}+".format( '-' * 30 ) )
		for i,option in enumerate( Menua.Options, 1 ):
			print( "| {}.- {:<25}|".format( i, option ) )
		print( "+{}+".format( '-' * 30 ) )

		while True:
			try:
				selected = int( input( "Egin zure aukera: " ) )
			except:
				print( "Aukera okerra, saiatu berriro." )
				continue
			if 0 < selected <= len( Menua.Options ):
				return selected
			else:
				print( "Aukera okerra, saiatu berriro." )

def iserror( message ):
	if( message.startswith( "ER" ) ):
		code = int( message[2:] )
		print( ER_MSG[code] )
		return True
	else:
		return False

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
	if len( sys.argv ) > 3:
		print( "Erabilera: {} [<zerbitzaria> [<portua>]]".format( sys.argv[0] ) )
		exit( 2 )

	if len( sys.argv ) >= 2:
		SERVER = sys.argv[1]
	if len( sys.argv ) == 3:
		PORT = int( sys.argv[2])

	s = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
	s.connect( (SERVER, PORT) )

	while True:
		user = input( "Erabiltzaile izena: " )
		message = "{}{}\r\n".format( szasar.Command.User, user )
		s.sendall( message.encode( "ascii" ) )
		message = szasar.recvline( s ).decode( "ascii" )
		if iserror( message ):
			continue

		password = input( "Pasahitza: " )
		message = "{}{}\r\n".format( szasar.Command.Password, password )
		s.sendall( message.encode( "ascii" ) )
		message = szasar.recvline( s ).decode( "ascii" )
		if not iserror( message ):
			break

	while True:
		option = Menua.menua()

		if option == Menua.List:
			message = "{}\r\n".format( szasar.Command.List )
			s.sendall( message.encode( "ascii" ) )
			message = szasar.recvline( s ).decode( "ascii" )
			if iserror( message ):
				continue
			filecount = 0
			print( "Zerbitzaritik jasotako fitxategi zerrenda" )
			print( "-----------------------------------------" )
			while True:
				line = szasar.recvline( s ).decode("ascii")
				if line:
					filecount += 1
					fileinfo = line.split( '?' )
					print( "{:<20} {:>8}".format( fileinfo[0], int2bytes( int(fileinfo[1]) ) ) )
				else:
					break
			print( "-------------------------------" )
			if filecount == 0:
				print( "Ez dago fitxategirik eskuragarri." )
			else:
				plurala = "{} fitxategi".format( filecount ) if filecount > 1 else "fitxategi bat"
				print( "Guztira {} eskuragarri.".format( plurala ) )

		elif option == Menua.Download:
			filename = input( "Idatzi jaitsi nahi duzun fitxategiaren izena: " )
			message = "{}{}\r\n".format( szasar.Command.Download, filename )
			s.sendall( message.encode( "ascii" ) )
			message = szasar.recvline( s ).decode ("ascii" )
			if iserror( message ):
				continue
			filesize = int( message[2:] )
			message = "{}\r\n".format( szasar.Command.Download2 )
			s.sendall( message.encode( "ascii" ) )
			message = szasar.recvline( s ).decode( "ascii" )
			if iserror( message ):
				continue
			filedata = szasar.recvall( s, filesize )
			try:
				with open( filename, "wb" ) as f:
					f.write( filedata )
			except:
				print( "Ezin da fitxategia disko lokalean gorde." )
			else:
				print( "'{}' fitxategia jaso da zuzenki.".format( filename ) )
    
		elif option == Menua.Upload:
			filename = input( "Idatzi igo nahi duzun fitxategiaren izena: " )
			filepath = input( "Sartu fitxategia dagoen direktorioa: ")
			fileinfo = filepath + '/' + filename
			message = "{}{}\r\n".format( szasar.Command.Upload, fileinfo )
			s.sendall( message.encode("ascii") )
			message = szasar.recvline( s ).decode( "ascii" )
			if iserror( message ):
				continue
			filesize = int( message[2:] )
			message = "{}\r\n".format( szasar.Command.Upload2 )
			s.sendall( message.encode( "ascii" ) )
			message = szasar.recvline( s ).decode( "ascii" )
			if iserror( message ):
				continue
			filedata = szasar.recvall( s, filesize )
			try:
				filename = os.path.join( "files", filename)
				with open( filename, "wb" ) as f:
					f.write( filedata )
			except:
				print( "Ezin da fitxategia igo." )
			else:
				print( "'{}' fitxategia igo da zuzenki.".format( filename ) )

		elif option == Menua.Delete:
			filename = input( "Idatzi ezabatu nahi duzun fitxategiaren izena: " )
			message = "{}{}\r\n".format( szasar.Command.Delete, filename )
			s.sendall( message.encode( "ascii" ) )
			message = szasar.recvline( s ).decode( "ascii" )
			if not iserror( message ):
				print( "'{}' fitxategia ezabatu da.".format( filename ) )

		elif option == Menua.Exit:
			message = "{}\r\n".format( szasar.Command.Exit )
			s.sendall( message.encode( "ascii" ) )
			message = szasar.recvline( s ).decode( "ascii" )
			break
	s.close()
