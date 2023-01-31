
import glob
from matplotlib import projections
import moviepy.editor as mpy
import natsort
import biraketak as bir
from scipy.interpolate import splprep, splev
import matplotlib.pyplot as plt
import numpy as np
from math import pi

def diskretizatu(num):
    lista = [0]
    tartea = 1/num
    for i in range(num):
        lista.append(lista[i]+tartea)
    return lista


puntuak1 = np.array([[0, 0, 0],[0, 0.2, 0.4], [0, 1.5, 0.8], [0, 4, 1], [0, 5, 2], [0, 5, 0]]).T
puntuak2 = np.array([[0, 0, 0],[0.1, 0.05, 0], [0.6, 0.8, 0], [0.9, 3.2, 0], [1.6, 4.5, 0],[0, 5, 0]]).T
puntuak3 = np.array([[0, 0, 0],[-0.1, 0.05, 0], [-0.6, 0.8, 0], [-0.9, 3.2, 0], [-1.6, 4.5, 0],[0, 5, 0]]).T

t_kurba = np.linspace(0, 1, 100)

#Rodrigues aplikatu
theta = pi/4
w1 = [-1, -1, 0]

puntuak_R1 = np.dot(bir.rodrigues(theta,w1), puntuak1)
puntuak_R2 = np.dot(bir.rodrigues(theta,w1), puntuak2)
puntuak_R3 = np.dot(bir.rodrigues(theta,w1), puntuak3)

basis_splinea_PR1, t_PR1 = splprep(puntuak_R1, k=3, s=0)
basis_splinea_PR2, t_PR2 = splprep(puntuak_R2, k=3, s=0)
basis_splinea_PR3, t_PR3 = splprep(puntuak_R3, k=3, s=0)

bs_kurba_R1_1 = splev(t_kurba, basis_splinea_PR1)
bs_kurba_R2_1 = splev(t_kurba, basis_splinea_PR2)
bs_kurba_R3_1 = splev(t_kurba, basis_splinea_PR3)

fig = plt.figure()
ax = fig.add_subplot(projection = '3d')

ax.plot(bs_kurba_R1_1[0], bs_kurba_R1_1[1], bs_kurba_R1_1[2], 'b-')
ax.plot(bs_kurba_R2_1[0], bs_kurba_R2_1[1], bs_kurba_R2_1[2], 'b-')
ax.plot(bs_kurba_R3_1[0], bs_kurba_R3_1[1], bs_kurba_R3_1[2], 'b-')

ax.set_xlim(-5, 5)
ax.set_ylim(-5, 5)
ax.set_zlim(-5, 5)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

#Rodrigues bigarren aldiz aplikatu
theta2 = pi/2
w2 = [0, 1, 1]

puntuak2_R1 = np.dot(bir.rodrigues(theta2,w2), puntuak1)
puntuak2_R2 = np.dot(bir.rodrigues(theta2,w2), puntuak2)
puntuak2_R3 = np.dot(bir.rodrigues(theta2,w2), puntuak3)

basis_splinea2_PR1, t2_PR1 = splprep(puntuak2_R1, k=3, s=0)
basis_splinea2_PR2, t2_PR2 = splprep(puntuak2_R2, k=3, s=0)
basis_splinea2_PR3, t2_PR3 = splprep(puntuak2_R3, k=3, s=0)

bs_kurba2_R1 = splev(t_kurba, basis_splinea2_PR1)
bs_kurba2_R2 = splev(t_kurba, basis_splinea2_PR2)
bs_kurba2_R3 = splev(t_kurba, basis_splinea2_PR3)

fig = plt.figure()
ax = fig.add_subplot(projection = '3d')

ax.plot(bs_kurba2_R1[0], bs_kurba2_R1[1], bs_kurba2_R1[2], 'b-')
ax.plot(bs_kurba2_R2[0], bs_kurba2_R2[1], bs_kurba2_R2[2], 'b-')
ax.plot(bs_kurba2_R3[0], bs_kurba2_R3[1], bs_kurba2_R3[2], 'b-')

ax.set_xlim(-5, 5)
ax.set_ylim(-5, 5)
ax.set_zlim(-5, 5)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

#Koaternoiak aplikatu

p = bir.quaternion(theta, w1)
q = bir.quaternion(theta2, w2)

s = []
n = 50
t = diskretizatu(n)

for i in range(len(t)):
    s.append(bir.SLInterp(p,q,t[i]))

for i in range(len(s)):
    p1quater = bir.quat_dot_curve(s[i], puntuak1)
    p2quater = bir.quat_dot_curve(s[i], puntuak2)
    p3quater = bir.quat_dot_curve(s[i], puntuak3)

    basis_splinea1_quat, t_puntuak1_quater = splprep(p1quater, k=3, s=0)
    basis_splinea2_quat, t_puntuak2_quater = splprep(p2quater, k=3, s=0)
    basis_splinea3_quat, t_puntuak3_quater = splprep(p3quater, k=3, s=0)

    bs_kurba1_quater = splev(t_kurba, basis_splinea1_quat)
    bs_kurba2_quater = splev(t_kurba, basis_splinea2_quat)
    bs_kurba3_quater = splev(t_kurba, basis_splinea3_quat)

    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')

    ax.plot(bs_kurba1_quater[0], bs_kurba1_quater[1], bs_kurba1_quater[2], 'b-')
    ax.plot(bs_kurba2_quater[0], bs_kurba2_quater[1], bs_kurba2_quater[2], 'b-')
    ax.plot(bs_kurba3_quater[0], bs_kurba3_quater[1], bs_kurba3_quater[2], 'b-')
    
    ax.set_xlim(-5, 5)
    ax.set_ylim(-5, 5)
    ax.set_zlim(-5, 5)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.savefig("./figures/"+str(i+1))
    plt.close()
    
    #Irudiak karpetatik atera
    file_list = glob.glob('./figures/*.png')
    
    #Alfabetikoki ordenatu
    seq = natsort.natsorted(file_list)
    
    #Kontrako ordenean
    seq_ald = natsort.natsorted(file_list, reverse = True)
    
    #Sekuentzia sortu
    clip = mpy.ImageSequenceClip(seq+seq_ald, fps=24)
    clip.write_gif('animazioa.gif')