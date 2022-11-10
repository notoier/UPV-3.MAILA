
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

puntuak = np.array([[1, 1, 2], [2, 2, 3], [3, 3, 3], [3, 4, 3], [3, 4, 5]]).T

t_kurba = np.linspace(0, 4, 100)

cr_kurba = np.zeros((3,100))
for k in range(100):
    cr_kurba[:,k] = gamma_CR(puntuak, 1/3, t_kurba[k])


fig = plt.figure()
ax = fig.add_subplot(projection = '3d')

ax.plot(puntuak[0,:], puntuak[1,:], puntuak[2,:], 'ro')
ax.plot(cr_kurba[0], cr_kurba[1], cr_kurba[2], 'b-')

ax.set_xlim(0, 5)      
ax.set_ylim(0, 5)
ax.set_zlim(0, 5)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()
