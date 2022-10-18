#!/usr/bin/env python3

import socket, sys

"""IKASLEAK BETETZEKO:
DNS zerbitzariaren IP helbidea "/etc/resolv.conf" fitxategian aurkituko duzu.
"""
DNS_DIR = '127.0.0.53'
DNS_PORT = '53'


def dns_izena_lortu(mezua, pos):
    
    hasierakoa = pos
    qname = ''  # Domeinu izena aldagai honetan osatzen joango gara
    tam_label = mezua[pos]
    print(format(tam_label, 'b').zfill(8))
    pos += 1
    byte_kop = 0
    while tam_label:
        if format(tam_label, 'b').zfill(8)[:2] == '00':  # Ez da izen konpresioa erabiltzen
            byte_kop += tam_label
            etiketa_mezua = mezua[pos + 1:pos + tam_label].decode('UTF-8')
            qname += etiketa_mezua
            pos += tam_label
            tam_label = mezua[pos]
            if tam_label != 0:
                qname += '.'

        else:  # Izen konpresioa erabiltzen da
            despl = int.from_bytes(mezua[pos - 1:pos + 1], 'big')  # Desplazamenduko 2 byteak irakurri
            despl &= 0x3fff  # Lehenengo 2 bitak 0 bihurtu
            pos += 1
            _, name = dns_izena_lortu(mezua, despl)
            qname += name
            break
    return byte_kop, qname


# Programa nagusia
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Erabilera: python3 {} <Domeinu izena>".format(sys.argv[0]))
        exit(1)

    izena = sys.argv[1]

    dns_zerb = (DNS_DIR, DNS_PORT)

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    print(izena)
    print(izena.encode('UTF-8'))
    domeinua = dns_izena_lortu(izena.encode('UTF-8'), 0)
    domeinu_byte_kop = domeinua[0]
    domeinu_izena = domeinua[1].encode('ascii')

    id_galdera = b'fu'
    buf = id_galdera + b'\x01\x00\x00\x01\x00\x00\x00\x00\x00\x00' + domeinu_izena + b'\x00\x01\x00\x01'

    s.sendto(buf, dns_zerb)  # Galdera bidali
    buf = s.recv(1024)  # Erantzuna jaso
    pos = 0  # Erantzuneko zenbatgarren bytea aztertzea tokatzen zaigun gordeko du
    # buf aldagaitik eremu bat irakurtzen dugun bakoitzean eguneratu beharko da
    
    id_erantzuna = buf[0:1]
    if id_galdera != id_erantzuna:
        print('Galderaren eta erantzunaren identifikadoreak desberdinak dira!')

    flags = int.from_bytes(buf[2:3], 'big')
    qr = flags / 1e16
    if qr != 1:
        print('Jasotakoa ez da erantzuna!')
    rcode = flags % 10_000
    if rcode != 0:
        print('Errorea egon da!')
    ancount = buf[6:7]
    if ancount == b'00':
        exit(0)
    type = buf[18 + 2 * domeinu_byte_kop: 19 + 2 * domeinu_byte_kop]
    clazz = buf[20 + 2 * domeinu_byte_kop: 21 + 2 * domeinu_byte_kop]
    if clazz == b'01':
        rdata = buf[28 + 2 * domeinu_byte_kop:]
        if type == b'01':
            print(rdata)

    s.close()
