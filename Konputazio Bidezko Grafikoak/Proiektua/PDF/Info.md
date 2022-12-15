# PROGRAM INFORMATION

## COMPILATION LINES

=====================

Compilation command line: gcc *.c -lGL -lGLU -lglut -lm

## PROGRAM FUNCTIONALITIES

===========================

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
[A,a] Aldaketak argiei eragin
[+] Objektuak aukeratu badira ardatz guztietan handitu. Kameraren kasuan ikuste bolumena handitu
[-] Objektuak aukeratu badira ardatz guztietan txikitu. Kameraren kasuan ikuste bolumena txikitu
[Z,z] Aldaketak desegin
<!-- 
    Translation matrix = [[1, 0, 0, Tx]
                          [0, 1, 0, Ty]
                          [0, 0, 1, Tz]
                          [0, 0, 0, 1 ]]

    Rotation matrix =    [[cos(beta) * cos(gamma), [cos(beta) * sin(gamma), -sin(beta), 0.0], 
                          [sin(alpha) * sin(beta) * cos (gamma) - cos(alpha) * sin(gamma), sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma), sin(alpha) * cos(beta), 0.0], 
                          [cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma), cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma), cos(alpha) * cos(beta), 0.0], 
                          [0.0, 0.0, 0.0, 1.0] ]

    Scale matrix =       [[Sx, 0,  0, 0]
                          [0, Sy,  0, 0]
                          [0,  0, Sz, 0]
                          [0,  0,  0, 1]]
 -->
## LINKS

===========

[OpenGl matrix's](https://solarianprogrammer.com/2013/05/22/opengl-101-matrices-projection-view-model/)
[Egela: 0.Fasea](https://egela.ehu.eus/pluginfile.php/6925238/mod_resource/content/2/Praktika_martxan_jartzen.pdf)
[Egela: 1.Fasea](https://egela.ehu.eus/mod/resource/view.php?id=5571269)
[Egela: 2.Fasea](https://egela.ehu.eus/mod/resource/view.php?id=5571272)
