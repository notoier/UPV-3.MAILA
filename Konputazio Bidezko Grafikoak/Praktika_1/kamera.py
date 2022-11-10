
from math import cos, sin, pi, sqrt
import numpy as np

# Funtzio hau kamera_ikuspegia funtzioan erabiliko da biraketa bati dagokion
# matrizea kalkulatzeko, eman behar zaio biraketaren angelua eta ardatzerdia

def rodrigues(theta_rad, bektorea):       
    array1d = np.array(bektorea)          
    w = array1d / sqrt(np.sum(array1d**2))                                  
    J = np.array( [[0,-w[2],w[1]], [w[2],0,-w[0]], [-w[1],w[0],0]] )
    I = np.eye(3)
    return I + sin(theta_rad) * J + (1 - cos(theta_rad)) * np.dot(J,J)     

# Espazio geometrikoan XYZ ardatzak ditugu, eskuin eskuaren arauaren arabera, eta Y da bertikala.
# Bionboak bi zati ditu, bat XY planoan eta bestea YZ planoan. Kameraren ikuspegiak X'Y' planoan
# puntuak emango ditu, berez espazioan dagoen bionboaren muturrei dagozkien puntuak plano batean.
# Kamera ikuspegiaren zehaztapenean kameraren orientazioa eman behar da, honela:
# - suposatu hasieran kamera Z negatiboaren gainean dagoela
# - biratu X ardatzaren inguruan, kamera gora edo behera begiratuz jarriko da
# - biratu Y ardatzaren inguruan, kamera biratuko da ardatz bertikalaren inguruan
#   (biraketak X+ eta Y+ ardatzerdien inguruan eskuin eskuaren arauaren arabera)
# Hauek dira kamera_ikuspegia funtzioaren parametroak, kamera ikuspegiaren zehaztapenak:
# - theta_x eta theta_y goian esan bezala, radianetan
# - P da kameraren posizioa, hiru koordenatu kartesiarren zerrenda
# - AB, AC, n, f parametroak orain ez dira aztertuko

def kamera_ikuspegia(theta_x, theta_y, P, AB, AC, n, f):
    
    # Kameraren biraketa matrizea prestatu
    R = np.dot(rodrigues(theta_y, [0,1,0]), rodrigues(theta_x, [1,0,0]))
    # M_per kalkulatu hiru pausotan
    M = np.array([[1./AB,0,0,0], [0,1./AC,0,0], [0,0,1./f,0], [0,0,0,1]])
    M = M.dot(np.row_stack((np.column_stack((R.T, [0,0,0])), [0,0,0,1])))
    M = M.dot(np.row_stack((np.column_stack((np.eye(3), - np.array(P))), [0,0,0,1])))
    # M_pp idatzi eta M_pp * M_per kalkulatu
    dif = float(f - n)
    M = np.array([[1,0,0,0], [0,1,0,0], [0,0,f/dif,n/dif], [0,0,-1,0]]).dot(M)

    # Bionboaren muturrak XYZ espazioan gehi bionboaren bi zatien zentroak, guztira zortzi puntu 
    puntu_zerrenda = [[0,0,0], [1,0,0], [1,2,0], [0,2,0], [0,2,1], [0,0,1], [0.5,1,-0.2], [0.2,1,0.5]]
    puntu_zerrenda_homog = np.row_stack((np.column_stack(puntu_zerrenda), np.ones(len(puntu_zerrenda))))
    transf_homog_gabe = M.dot(puntu_zerrenda_homog)
    # Kamera ikuspegian puntuen x,y koordenatuak itzuli, kamera ondo badago, bestela oharra
    if (transf_homog_gabe[2,:] > 0).any():
        print('Kamera gaizki kokatu da') 
    else:
        puntuak_kameran_homog = transf_homog_gabe[0:4,:]/transf_homog_gabe[3,:]
        return puntuak_kameran_homog[0:2,:]



