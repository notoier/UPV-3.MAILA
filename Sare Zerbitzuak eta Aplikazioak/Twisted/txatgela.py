#!/usr/bin/env python3

from twisted.protocols.basic import LineReceiver
from twisted.internet.protocol import Factory
from twisted.internet import reactor

MAX_USERS = 100
MAX_MSG_LENGTH = 255
MAX_USER_LENGTH = 16
PORT = 8000

class ChatFactory(Factory):
    def __init__(self):
        self.users = {}
        self.features = { 'FILES':'0' , 'CEN':'0', 'NOP':'0', 'SSL':'0' } 

    def buildProtocol(self, addr):
        return ChatProtocol(self)

class ChatProtocol(LineReceiver):
    def __init__(self, factory: ChatFactory):
        self.factory = factory
        self.name = None

    def connectionMade(self):
        # FTR
        ftr = self.factory.features
        self.sendLine(f"FTR{ftr['FILES']} {ftr['CEN']} {ftr['NOP']} {ftr['SSL']}".encode('utf-8'))

        # DAGOENEKO KONEKTATUTA DAUEDEN ERABILTZAILEEN IZENAK OHARTARAZI
        p = ""
        for user in self.factory.users:
            p += f"{user} "

        if p != "":
            usr = f"USR{p[:-1]}"
            self.sendLine(usr.encode('utf-8'))
        else:
            self.sendLine("USR".encode('utf-8'))


    def connectionLost(self, reason):
        for user in self.factory.users:
            user.sendLine(f"OUT{self.name}".encode('utf-8'))

    def lineReceived(self, line):
        line = line.decode('utf-8')

        print(line)
        
        c = line[0:3]
        p = line[3:].split(" ")

        if c == "NME":
            self.izenaz_ohartarazi(p[0])
        elif c == "MSG":
            self.mezua_bidali(p[0])

        self.sendLine("+".encode('utf-8'))
    
    def izenaz_ohartarazi(self, izena):        
        # Bezero berria sartu
        self.name = izena

        # Besteak ohartarazi
        for user in self.factory.users.values():
            user.sendLine(f"INN{self.name}".encode('utf-8'))

        self.factory.users[izena] = self
    
    def mezua_bidali(self, mezua):
        for user in self.factory.users.values():
            user.sendLine(f"MSG{self.name} {mezua}".encode('utf-8'))

if __name__ == "__main__":
	reactor.listenTCP(PORT, ChatFactory())
	reactor.run()
