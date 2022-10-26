from random import randint
from matplotlib.cbook import simple_linear_interpolation
import numpy as np
import matplotlib.pyplot as plt

import sys
sys.path.append('/Visual Studio Code Projects/Konputazio Bidezko Grafikoak/3.Praktika')
from biraketak import quaternion, SLInterp, quat_dot_curve, rodrigues

from scipy.interpolate import splprep, splev, BSpline

kurba_puntuak = np.array([[1.5, 5, 0], [2.5, 5, 0], [3.5, 5, 0], [2.5, 5, 1], [2.5, 1.5, 0]]).T
kurba1 = np.array([[1.5, 5, 0], [1.75, 4, 0], [2.25, 3, 0], [2.25, 1.75, 0], [2.5, 1.5, 0]]).T
kurba2 = np.array([[3.5, 5, 0], [3.25, 4, 0], [2.75, 3, 0], [2.75, 1.75, 0], [2.5, 1.5, 0]]).T
kurba3 = np.array([[2.5, 5, 1], [2.5, 4, 0.75], [2.5, 3, 0.25], [2.5, 1.75, 0.25], [2.5, 1.5, 0]]).T
line1 = np.array([[1.5, 5, 0], [3.5, 5, 0]]).T
line2 = np.array([[2.5, 5, 0], [2.5, 5, 1]]).T

basis_splinea, t_puntuak = splprep(kurba1, k=3, s=0)
basis_splinea2, t_puntuak2 = splprep(kurba2, k=3, s=0)
basis_splinea3, t_puntuak3 = splprep(kurba3, k=3, s=0)
basis_splinea4, t_kurba4 = splprep(line1, k=1, s=1)
basis_splinea5, t_kurba5 = splprep(line2, k=1, s=1)


t_kurba = np.linspace(0, 1, 100)   # orain [0, 1] tartea

bs_kurba = splev(t_kurba, basis_splinea)
bs_kurba2 = splev(t_kurba, basis_splinea2)
bs_kurba3 = splev(t_kurba, basis_splinea3)
bs_lerroa = splev(t_kurba, basis_splinea4)
bs_lerroa2 = splev(t_kurba, basis_splinea5)

#Rodrigues



fig = plt.figure()
ax = fig.add_subplot(projection='3d')


ax.plot(kurba_puntuak[0,:], kurba_puntuak[1,:], kurba_puntuak[2,:], 'ro')

ax.plot(bs_kurba[0], bs_kurba[1], bs_kurba[2], 'b-')
ax.plot(bs_kurba2[0], bs_kurba2[1], bs_kurba2[2], 'b-')
ax.plot(bs_kurba3[0], bs_kurba3[1], bs_kurba3[2], 'b-')
ax.plot(bs_lerroa[0], bs_lerroa[1], bs_lerroa[2], 'b-')
ax.plot(bs_lerroa2[0], bs_lerroa2[1], bs_lerroa2[2], 'b-')



ax.set_xlim(0, 5)      
ax.set_ylim(0, 5)
ax.set_zlim(0, 5)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')


#ax.view_init(alpha, beta)

p = quaternion(np.pi / 4, [1, 1, 1])
q = quaternion(np.pi, [1, 0, 0])

t = np.linspace(0, 1, 100)
for k in range(50):
    s = SLInterp(p,q,t[k])
    
    ax.cla()
    
    #ardatzean mugak
    ax.set_xlim(0, 5)      
    ax.set_ylim(0, 5)
    ax.set_zlim(0, 5)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    
    bs_kurba_r1 = quat_dot_curve(s, bs_kurba)
    bs_kurba_r2 = quat_dot_curve(s, bs_kurba2)
    bs_kurba_r3 = quat_dot_curve(s, bs_kurba3)
    
    bs_lerroa_r1 = quat_dot_curve(s, bs_lerroa)
    bs_lerroa_r2 = quat_dot_curve(s, bs_lerroa2)
    
    color = ['b-','r-']
    c = color[0] if k % 2 == 0 else color[1]
       
    ax.plot(bs_kurba_r1[0], bs_kurba_r1[1], bs_kurba_r1[2], c)
    ax.plot(bs_kurba_r2[0], bs_kurba_r2[1], bs_kurba_r2[2], c)
    ax.plot(bs_kurba_r3[0], bs_kurba_r3[1], bs_kurba_r3[2], c)
    ax.plot(bs_lerroa_r1[0], bs_lerroa_r1[1], bs_lerroa_r1[2], c)
    ax.plot(bs_lerroa_r2[0], bs_lerroa_r2[1], bs_lerroa_r2[2], c)
        
    
    plt.pause(0.2)
    
#Ibilbide animazioa

bidea = np.array([[2.5, 2.5, 2.5], [2.5, 2.5, 3.5], [2.5, 4.5, 3.5], [3.5, 3.5, 3.5], [2.5, 2.5, 2.5]])
basis_splinea_bidea, t_puntuak_bidea = splprep(bidea, k=2, s=1)
bs_bidea = splev(t_kurba, basis_splinea_bidea) 


t = np.linspace(0,1,50)
for k in range(0, 50):
    
    puntua = np.array([[bs_bidea[0][k], bs_bidea[1][k], bs_bidea[2][k]]]).T
    
    ax.cla()
    
    #ardatzean mugak
    ax.set_xlim(0, 5)      
    ax.set_ylim(0, 5)
    ax.set_zlim(0, 5)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    
    bs_kurba_r1 = quat_dot_curve(s, bs_kurba) + puntua
    bs_kurba_r2 = quat_dot_curve(s, bs_kurba2) + puntua
    bs_kurba_r3 = quat_dot_curve(s, bs_kurba3) + puntua
    
    bs_lerroa_r1 = quat_dot_curve(s, bs_lerroa) + puntua
    bs_lerroa_r2 = quat_dot_curve(s, bs_lerroa2) + puntua
    
    color = ['b-','r-']
    c = color[randint(0,1)]
    
    ax.plot(bs_kurba_r1[0], bs_kurba_r1[1], bs_kurba_r1[2], c)
    ax.plot(bs_kurba_r2[0], bs_kurba_r2[1], bs_kurba_r2[2], c)
    ax.plot(bs_kurba_r3[0], bs_kurba_r3[1], bs_kurba_r3[2], c)
    ax.plot(bs_lerroa_r1[0], bs_lerroa_r1[1], bs_lerroa_r1[2], c)
    ax.plot(bs_lerroa_r2[0], bs_lerroa_r2[1], bs_lerroa_r2[2], c)
    
    plt.pause(0.2)
    