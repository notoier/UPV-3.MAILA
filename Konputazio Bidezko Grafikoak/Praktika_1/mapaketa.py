import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
from math import pi
import kamera as km
import random

# Ehundura maparen irudi digitala irakurri, PNG formatoa duen artxiboa:
hikone_irudia = mpimg.imread('Hikone_Screen_bi_zati.png')
# Matrize batean jaso da irudia, pixelak lerroka eta zutabeka daude, kolorea RGB
hikone_irudia.shape
# Matrize koadroa denez, zabalera gorde:
h_zabal = 1591
# Irudia ikusteko:
plt.imshow(hikone_irudia)
plt.show()

# Ehundura mapan u,v koordenatuetatik pixel matrizeko i,j indizeak lortzeko funtzioa:
# u,v koordenatuen balioak (float): u ardatz horizontala [-1,1] eta v bertikala [0,2] 
# indizeen balioak (int): i lerroa 0,...,h_zabal-1 eta j zutabea 0,...,h_zabal-1
def pixel_indizeak(u, v):
    fakt = h_zabal - 1
    return int(round((2 - v) * 0.5 * fakt)), int(round((u + 1) * 0.5 * fakt))
# Ehundura mapan bionboaren muturrei dagozkien (u,v) puntuak hartuz, pixel egokiak ditugu?
h_zabal
pixel_indizeak(0, 0)
pixel_indizeak(1, 0)
pixel_indizeak(1, 2)
pixel_indizeak(0, 2)
pixel_indizeak(-1, 2)
pixel_indizeak(-1, 0)

# Kameraren bidez XYZ espazioan dagoen bionboaren muturrak X'Y' planoko puntu bezala ikusiko
# ditugu, puntu horiek mugatzen duten poligonoaren gainean egin behar da ehundura mapaketa,
# bi atalen zentroak ere hartuko ditugu triangelu sarea definitzeko. Vxy matrizea lortuko
# dugu, honek bi lerro ditu puntuen x, y koordenatuekin eta bere zutabeak dira poligonoaren
# erpinak V0, V1, ... , V5 eta bi zatien zentroak V6, V7:
Vxy = km.kamera_ikuspegia(-pi/20, 5*pi/9, [1.75, 1.6, 1.25], 1, 1, 0.1, 1) 
# Marraztu V0, V1, ... , V5 poligonoa:
plt.plot(Vxy[0,0:6], Vxy[1,0:6], 'b-')
# Itxi poligonoa:
plt.plot([Vxy[0,0],Vxy[0,5]], [Vxy[1,0],Vxy[1,5]], 'b-')
# Bi zentroak ere:
plt.plot(Vxy[0,6:8], Vxy[1,6:8], 'bo')
# Ikus marrazkia. Parametro hauek aldatu pixka bat: bi angeluak, posizioa; besteak ez ukitu.
plt.show()

# X'Y' planoko triangelu sarea
triangeluak_xy = [
np.column_stack((Vxy[:,6],Vxy[:,0],Vxy[:,1])),np.column_stack((Vxy[:,6],Vxy[:,1],Vxy[:,2])),
np.column_stack((Vxy[:,6],Vxy[:,2],Vxy[:,3])),np.column_stack((Vxy[:,6],Vxy[:,3],Vxy[:,0])),
np.column_stack((Vxy[:,7],Vxy[:,0],Vxy[:,3])),np.column_stack((Vxy[:,7],Vxy[:,3],Vxy[:,4])),
np.column_stack((Vxy[:,7],Vxy[:,4],Vxy[:,5])),np.column_stack((Vxy[:,7],Vxy[:,5],Vxy[:,0]))]
# Aprobetxatu hau UV planoko triangelu sarea idazteko, egin Find & Replace modu egokian


triangeluak_uv = [
np.column_stack(([0.5,1],[0,0],[1,0])),np.column_stack(([0.5,1],[1,0],[1,2])),
np.column_stack(([0.5,1],[1,2],[0,2])),np.column_stack(([0.5,1],[0,2],[0,0])),
np.column_stack(([-0.5,1],[0,0],[0,2])),np.column_stack(([-0.5,1],[0,2],[-1,2])),
np.column_stack(([-0.5,1],[-1,2],[-1,0])),np.column_stack(([-0.5,1],[-1,0],[0,0]))]
###
#M⁻1 zortzi triangelutan
Malderantzizkoak = []
for triangelua in triangeluak_xy:
   M = np.row_stack((triangelua,[1,1,1]))
   Malderantzizkoak.append(np.linalg.inv(M))
###

# X'Y' planoan dugun poligonoa barruan hartuko duen koadroa finkatu behar da, koadroa 
# zehazteko hartuko ditugu goiko ezkerreko erpinaren koordenatuak, koad_0_x eta koad_0_y,  
# eta koadroaren aldea, koad_l. Koadroaren gainean sortuko dugu irudi digital berria, 
# kamerarekin lortu dugun poligonoaren gainean Hikone pantailaren mapaketa izango duena.
# Hasteko mapaketa irudi txuria, pixel matrizea zabalera honekin:
m_zabal = 500
# Kontuz, makal badoa idatzi 500 probak egiteko, azken exekuzioan 1000 
mapaketa_irudia = np.ones((m_zabal, m_zabal, 3))
# Mapaketa irudiko matrizearen pixel baten indizeetatik X'Y' planoan dagokion puntuaren
# koordenatu kartesiarrak lortzeko funtzioa:
def koadroa_xy(i, j): 
    koad_0_x = 0.25
    koad_0_y = 1.10
    koad_l = 3
    zatitz = float(m_zabal - 1)
    return koad_0_x + koad_l * j / zatitz, koad_0_y - koad_l * i / zatitz
# Funtzioa ondo dago?
print(koadroa_xy(0, 0))
print(koadroa_xy(m_zabal-1, 0))
print(koadroa_xy(m_zabal-1, m_zabal-1))
print(koadroa_xy(0, m_zabal-1))


# PRAKTIKAK ESKATZEN DUENA: lortu X'Y' planoko poligonoaren ehundura mapaketa, hau da, 
# mapaketa irudiaren pixelei koloreak esleitu Hikone irudia erabiliz ehundura mapa bezala.
#
# PROGRAMATU BEHAR DENA:
#
# X'Y' planoko triangelu sareari ehundura mapan dagokion UV planoko triangelu sarea 
# definitu, triangeluak_uv zerrenda adibidez. Triangeluak np.array matrizeak dira, erpinen
# u,v koordenatuak zutabeka idatziz. 
#
# Lehenenik, triangeluak_xy triangelu zerrendan kalkulatu koordenatu barizentrikoak
# lortzeko gero erabiliko diren M matrizeen alderantzizkoak eta gorde zerrenda batean.
#
# for bikoitza mapaketa_irudia pixel matrizea zeharkatzeko lerroka eta zutabeka,
# eta for triangeluen zerrenda zeharkatzeko:
# kalkulatu pixelari dagokion (x,y) puntuaren koordenatu barizentrikoak triangeluan
# if puntua triangelu barruan dago? 
# horrela bada, lortu puntuari dagozkion mapako u,v koordenatuak interpolazio 
# barizentrikoaren bidez eta mapako puntu honi Hikone irudian dagokion pixelaren kolorea
# eman mapaketa irudiko pixelari (puntua triangeluan ez badago ezer ez egin)
#
# ikusi mapaketa irudia

for i in range(0,m_zabal):
    for j in range(0,m_zabal):
        for t in range(0,8):
            xy = koadroa_xy(i,j)
            koord_bariz = Malderantzizkoak[t].dot([xy[0], xy[1],1])
            if np.all(koord_bariz >= 0):
                koord_uv = triangeluak_uv[t].dot(koord_bariz)
                pixels = pixel_indizeak(koord_uv[0], koord_uv[1])
                kolorea = hikone_irudia[pixels[0], pixels[1]]
                mapaketa_irudia[i][j] = kolorea
plt.imshow(mapaketa_irudia)
plt.show()
                #Kalkulatu mapako u,v koordenatuak
                #Koloreak begiratu mapan eta esleitu irudian
                #show mapaketa irudia 
