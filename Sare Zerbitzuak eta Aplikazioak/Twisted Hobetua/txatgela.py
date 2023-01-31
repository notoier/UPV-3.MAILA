#!/usr/bin/env python3

from twisted.protocols.basic import LineReceiver
from twisted.internet.protocol import Factory
from twisted.internet import reactor

MAX_USERS = 100
MAX_MSG_LENGTH = 255
MAX_USER_LENGTH = 16
PORT = 8000
BAD_WORD = '#####'
WAIT_TIME = 5

class ChatFactory(Factory):
    def __init__(self, bad_words):
        self.users = {}
        self.features = { 'FILES':'0' , 'CEN':'1', 'NOP':'1', 'SSL':'0' }
        self.bad_words = bad_words

    def buildProtocol(self, addr):
        return ChatProtocol(self)

class ChatProtocol(LineReceiver):
    def __init__(self, factory: ChatFactory):
        self.factory = factory
        self.name = None
        self.timer = None
        self.activity = False

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

        self.timer = reactor.callLater(WAIT_TIME, self.itxitasunaz_ohartarazi)
        self.activity = True


    def connectionLost(self, reason):
        for user in self.factory.users:
            user.sendLine(f"OUT{self.name}".encode('utf-8'))

    def lineReceived(self, line):
        if self.activity:
            self.timer.reset(WAIT_TIME)
        else:
            self.timer = reactor.callLater(WAIT_TIME, self.itxitasunaz_ohartarazi)
            self.activity = True

        line = line.decode('utf-8')
        
        c = line[0:3]
        p = line[3:].split(" ")

        if c == "NME":
            self.izenaz_ohartarazi(p[0])
        elif c == "MSG":
            self.mezua_bidali(self.hitz_txarrak_prozesatu(p))
        elif c == "WRT":
            self.idazten_ohartarazi()

        self.sendLine("+".encode('utf-8'))

    def izenaz_ohartarazi(self, izena):        
        # Bezero berria sartu
        self.name = izena

        # Besteak ohartarazi
        for chat_protocol in self.factory.users.values():
            chat_protocol.sendLine(f"INN{self.name}".encode('utf-8'))

        self.factory.users[izena] = self
    
    def mezua_bidali(self, mezua):
        for chat_protocol in self.factory.users.values():
            if chat_protocol == self:
                continue

            chat_protocol.sendLine(f"MSG{self.name} {mezua}".encode('utf-8'))

    def hitz_txarrak_prozesatu(self, mezua):
        ret = ""
        for hitza in mezua:
            if self.factory.bad_words.count(hitza.lower()) == 1:
                ret = ret + BAD_WORD + " "
            else:
                ret = ret + hitza + " "
        
        return ret[:-1]

    def idazten_ohartarazi(self):
        for chat_protocol in self.factory.users.values():
            if chat_protocol == self:
                continue

            chat_protocol.sendLine(f"WRT{self.name}".encode('utf-8'))
    
    def itxitasunaz_ohartarazi(self):
        self.sendLine("NOP".encode('utf-8'))
        self.activity = False

def init():
    # load bad words file
    with open("bad_words.csv", "r") as f:
        bad_words = f.read().split(", ")
    
    return bad_words

def main():
    bad_words = init()
    reactor.listenTCP(PORT, ChatFactory(bad_words))
    reactor.run()



if __name__ == "__main__":
    main()