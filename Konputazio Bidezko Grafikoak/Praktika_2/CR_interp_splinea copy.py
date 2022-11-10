
import mpl_toolkits.mplot3d
import numpy as np
import matplotlib.pyplot as plt
from math import floor

# Funtzio honek CR interpolazio splinearen puntuak kalkulatzen ditu. Argumentuak dira: 
# n+1 kontrol puntu zutabeka matrize batean, kontrol puntuetako deribatu-bektorearen 
# faktorea eta kurbaren parametroaren balioa [0,n] tartean. Kontrol puntuen indizeak
# 0, 1, ... , n dira eta horiek dira kurbaren parametroaren balioak kontrol puntuetan. 
def gamma_CR(p, r, t): 
    n = p.shape[1] - 1  
    M = np.array([[1, 0, -3, 2], [0, 0, 3, -2], [0, 1, -2, 1], [0, 0, -1, 1]])
    k = floor(t)    # gamma kurbako k segmentuan hartuko dugu Hermite kurba 
    Mt = M.dot([1, t-k, (t-k)**2, (t-k)**3])
    if t < 0 or t > n:
        print('errorea')
    elif k > 0 and k < n - 1: # atzeko eta aurreko kontrol puntuen indizeak k-1,k,k+1,k+2
        PQvw = (p[:,k], p[:,k+1], (p[:,k+1] - p[:,k-1]) * r, (p[:,k+2] - p[:,k]) * r)
        return np.column_stack(PQvw).dot(Mt)
    elif k == 0:
        PQvw = (p[:,k], p[:,k+1], 2 * (p[:,k+1] - p[:,k]) * r, (p[:,k+2] - p[:,k]) * r)
        return np.column_stack(PQvw).dot(Mt)
    elif k == n - 1:
        PQvw = (p[:,k], p[:,k+1], (p[:,k+1] - p[:,k-1]) * r, 2 * (p[:,k+1] - p[:,k]) * r)
        return np.column_stack(PQvw).dot(Mt)
    elif k == n:
        return p[:,n]

t_kurba = np.linspace(0, 4, 100)

puntuak = np.array([[1], [0], [0], [0], [0]]).T
cr_0 = np.zeros((1,100))
for k in range(100):
    cr_0[:, k] = gamma_CR(puntuak, 1/3, t_kurba[k])

plt.show()
