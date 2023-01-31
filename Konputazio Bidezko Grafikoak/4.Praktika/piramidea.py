
from math import cos, sin, pi, sqrt
from matplotlib import pyplot as plt
import numpy as np
import biraketak as bir

# Munduko ardatzak XYZ dira, ardatz bertikala Y izanik, ohiko orientazioarekin.
# Piramidearen oinarria ZX planoan kokatuko da.
# Funtzio honen argumentuak dira: 
# - N, piramideak zenbat aurpegi dituen, azpikoa kenduta
# - argi_iturria bektorea, argi direkzionala nondik datorren, infinituko argi iturria

def piramidea_sortu(N, argi_iturria):

    # Prestatu argiaren bektore unitarioa
    argi_bektorea = np.array(argi_iturria)
    argia = argi_bektorea / sqrt(np.sum(argi_bektorea**2))
    r = 1.5
    triangeluak = []
    distirak = []

    for k in range(N):

        # Triangeluaren hiru puntuak matrizean ipini zutabeka eta erantsi zerrendari
        theta1, theta2 = k*2*pi/N, (k+1)*2*pi/N        
        P1 = r * np.array([sin(theta1), 0, cos(theta1)])
        P2 = r * np.array([sin(theta2), 0, cos(theta2)])
        Q  = np.array([0, 3, 0])
        triangeluak.append(np.column_stack((P1, P2, Q)))
        
        # Normala kalkulatu, piramidetik kanpora begira, unitarioa
        QP1, QP2 = P1 - Q, P2 - Q
        biderk_bek = np.cross(QP1, QP2)
        normala = biderk_bek / sqrt(np.sum(biderk_bek**2))

        # Kalkulatu distira eta gorde (biderkadura negatiboa argiak ez badu jotzen)
        biderk_esk = np.dot(normala, argia)
        if biderk_esk > 0:
            distirak.append(biderk_esk)
        else:
            distirak.append(0.)

    return triangeluak, distirak


# Funtzio honek kalkulatuko ditu triangeluen koordenatuak 
# ikuspegi bolumen paralelo estandarreko koordenatu sisteman.
# Kameraren biraketa X eta Yren inguruko biraketen bidez definitzen da,
# theta_x eta theta_y angeluekin, kamera hasieran Z negatiboari begira kokatuz.
# P bektorea kameraren posizioa da, AB, AC, n, f kameraren ohiko parametroak.

def piramidea_paraleloan(triangeluak_munduan, theta_x, theta_y, P, AB, AC, n, f):

    # Kameraren biraketa matrizea
    R = np.dot(bir.rodrigues(theta_y, [0,1,0]), bir.rodrigues(theta_x, [1,0,0]))
    # M_per kalkulatu hiru pausotan
    M = np.array([[1./AB,0,0,0], [0,1./AC,0,0], [0,0,1./f,0], [0,0,0,1]])
    M = M.dot(np.row_stack((np.column_stack((R.T, [0,0,0])), [0,0,0,1])))
    M = M.dot(np.row_stack((np.column_stack((np.eye(3), - np.array(P))), [0,0,0,1])))
    # M_pp idatzi eta matrize guztien biderkadura kalkulatu
    dif = float(f - n)
    M = np.array([[1,0,0,0], [0,1,0,0], [0,0,f/dif,n/dif], [0,0,-1,0]]).dot(M)

    triangeluak_paraleloan = []
    for k in range(len(triangeluak_munduan)):
        triangelua_munduan_koord_homog = np.row_stack((triangeluak_munduan[k], [1,1,1]))
        transf_homog_gabe = M.dot(triangelua_munduan_koord_homog)
        if (transf_homog_gabe[2,:] > 0).any():
            print('Kamera gaizki kokatu da') 
            break
        triangelua_paraleloan_koord_homog = transf_homog_gabe[0:4,:]/transf_homog_gabe[3,:]
        triangeluak_paraleloan.append(triangelua_paraleloan_koord_homog[0:3,:])
    else:
        return triangeluak_paraleloan

def koadroa_xy(x,y, m_zabal):
    koad_1_x = -1
    koad_1_y = 1
    koad_l = 2
    zatitz = float(m_zabal-1)
    return koad_1_x + koad_l * y / zatitz, koad_1_y - koad_l * x / zatitz

def main():
    N = 24
    triangeluak = piramidea_sortu(N, [1, 0.5, 0])
    paraleloak = piramidea_paraleloan(triangeluak[0], pi/20, pi/4, [2, 0.5, 2], 5, 5, 1, 5)
    
    Mald = []
    for triangelua in paraleloak:
        column = np.column_stack((triangelua, [0, 0, -1]))
        row = np.row_stack((column, [1, 1, 1, 0]))
        inv = np.linalg.inv(row)
        Mald.append(inv)
    
    m_zabal = 1000
    piramidea = np.ones((m_zabal, m_zabal, 1))
    
    for i in range(m_zabal):
        for j in range(m_zabal):
            hurbil = float('+inf')
            for triangelua in range(len(triangeluak[0])):
                koord_barizentrikoa = Mald[triangelua].dot([koadroa_xy(i, j, m_zabal)[0], koadroa_xy(i, j, m_zabal)[1], 0, 1])
                
                if (koord_barizentrikoa[0] >= 0 and 
                    koord_barizentrikoa[1] >= 0 and 
                    koord_barizentrikoa[2] >= 0 and 
                    koord_barizentrikoa[3] < hurbil):
                    
                    hurbil = -koord_barizentrikoa[3]
                    piramidea[i, j] = triangeluak[1][triangelua]
    plt.imshow(piramidea)
    plt.show()
    
if __name__ == '__main__':
    main()

