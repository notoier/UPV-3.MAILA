# PROGRAM UTILS

=================

Compilation command line: gcc *.c -lGL -lGLU -lglut -lm

## PROGRAM FUNCTIONALITIES

=======================

[?] Laguntza pantailaratu
[ESC]  Programatik irten
[F,f]  Objektuak kargatu, *.obj fitxategi bat irakurriz
[TAB] Kargaturik dauden objektuen artean bat hautatu
[SUPR] Hautaturik dagoen objektua ezabatu
[-] Bistaratze-eremua txikitu
[+] Bistaratze-eremua handitu
[I,i] Aukeratutako objektuari buruzko informazioa pantailaratu

[T,t] Translazioa aktibatu
[R,r] Biraketa aktibatu
[E,e] Tamaina aldaketa aktibatu
[G,g] Aldaketak munduaren erreferentzi sisteman eragin (aldaketa globalak, alegia). Besterik ezean hau egongo da aktibo.
[L,l] Aldaketak objektuaren (edo kameraren, edo argiaren) erreferentzi sisteman eragin (aldaketa lokalak, alegia)
[GORA] Mugitu +Y; Txikitu Y; Biratu +X
[BEHERA] Mugitu -Y; Handitu Y; Biratu -X
[ESKUINA] Mugitu +X; Txikitu X; Biratu +Y
[EZKERRA] Mugitu -X; Handitu X; Biratu -Y
[AVPAG] Mugitu +Z; Txikitu Z; Biratu +Z
[REPAG] Mugitu -Z; Handitu Z; Biratu -Z
[O,o] Aldaketak objektuei eragin (besterik ezean hau izango da aukera)
[C,c] Aldaketak Kamerei eragin
[L,l] Aldaketak argiei eragin
[+] Objektuak aukeratu badira ardatz guztietan handitu. Kameraren kasuan ikuste bolumena handitu
[-] Objektuak aukeratu badira ardatz guztietan txikitu. Kameraren kasuan ikuste bolumena txikitu
[Z,z] Aldaketak desegin

    Translation matrix = [[1, 0, 0, Tx]
                          [0, 1, 0, Ty]
                          [0, 0, 1, Tz]
                          [0, 0, 0, 1 ]]

    Rotation matrix = Rx = [[1,  0,      0,      0]          Ry = [[cos(x),  0,  sin(x), 0]          Rz = [[cos(x), -sin(x), 0, 0] 
                            [0, cos(x), -sin(x), 0]                [  0,     1,    0,    0]                [sin(x), cos(x),  0, 0]
                            [0, sin(x), cos(x),  0]                [-sin(x), 0,  cos(x), 0]                [ 0,      0,      1, 0]
                            [0,  0,      0,      1]]               [  0,     0,    0,    1]]               [ 0,      0,      0, 1]]

    Scale matrix =       [[Sx, 0,  0, 0]
                          [0, Sy,  0, 0]
                          [0,  0, Sz, 0]
                          [0,  0,  0, 1]]

## LINKS

===========
[Github repository](https://www.google.com)
[OpenGl matrix's](https://solarianprogrammer.com/2013/05/22/opengl-101-matrices-projection-view-model/)
