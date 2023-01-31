#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec 29 17:48:22 2022

@author: ander
"""

import glob
import moviepy.editor as mpy
import natsort
import biraketak as bir
from scipy.interpolate import splprep, splev
import matplotlib.pyplot as plt
import numpy as np
from math import sqrt, sin, cos, acos, pi

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

#RODRIGUES 1
theta=pi/4
w1=[-1,-1,0]

puntuak_Rodr1 = np.dot(bir.rodrigues(theta,w1),puntuak1)
puntuak2_Rodr1 = np.dot(bir.rodrigues(theta,w1),puntuak2)
puntuak3_Rodr1 = np.dot(bir.rodrigues(theta,w1),puntuak3)

basis_splinea1_Rodr1, t_puntuak1_Rodr1 = splprep(puntuak_Rodr1, k=3, s=0) #Spline kubikoa, leuntasuna s=0 eta s=1 hartu
basis_splinea2_Rodr1, t_puntuak2_Rodr1 = splprep(puntuak2_Rodr1, k=3, s=0)
basis_splinea3_Rodr1, t_puntuak3_Rodr1 = splprep(puntuak3_Rodr1, k=3, s=0)

bs_kurba1_Rodr1 = splev(t_kurba, basis_splinea1_Rodr1)
bs_kurba2_Rodr1 = splev(t_kurba, basis_splinea2_Rodr1)
bs_kurba3_Rodr1 = splev(t_kurba, basis_splinea3_Rodr1)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.plot(bs_kurba1_Rodr1[0], bs_kurba1_Rodr1[1], bs_kurba1_Rodr1[2], 'b-')
ax.plot(bs_kurba2_Rodr1[0], bs_kurba2_Rodr1[1], bs_kurba2_Rodr1[2], 'b-')
ax.plot(bs_kurba3_Rodr1[0], bs_kurba3_Rodr1[1], bs_kurba3_Rodr1[2], 'b-')

ax.set_xlim(-5, 5)
ax.set_ylim(-5, 5)
ax.set_zlim(-5, 5)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

#RODRIGUES 2
theta2=pi/2
w2=[0,1,1]

puntuak_Rodr2 = np.dot(bir.rodrigues(theta2,w2),puntuak1)
puntuak2_Rodr2 = np.dot(bir.rodrigues(theta2,w2),puntuak2)
puntuak3_Rodr2 = np.dot(bir.rodrigues(theta2,w2),puntuak3)

basis_splinea1_Rodr2, t_puntuak1_Rodr2 = splprep(puntuak_Rodr2, k=3, s=0)
basis_splinea2_Rodr2, t_puntuak2_Rodr2 = splprep(puntuak2_Rodr2, k=3, s=0)
basis_splinea3_Rodr2, t_puntuak3_Rodr2 = splprep(puntuak3_Rodr2, k=3, s=0)

bs_kurba1_Rodr2 = splev(t_kurba, basis_splinea1_Rodr2)
bs_kurba2_Rodr2 = splev(t_kurba, basis_splinea2_Rodr2)
bs_kurba3_Rodr2 = splev(t_kurba, basis_splinea3_Rodr2)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.plot(bs_kurba1_Rodr2[0], bs_kurba1_Rodr2[1], bs_kurba1_Rodr2[2], 'b-')
ax.plot(bs_kurba2_Rodr2[0], bs_kurba2_Rodr2[1], bs_kurba2_Rodr2[2], 'b-')
ax.plot(bs_kurba3_Rodr2[0], bs_kurba3_Rodr2[1], bs_kurba3_Rodr2[2], 'b-')

ax.set_xlim(-5, 5)
ax.set_ylim(-5, 5)
ax.set_zlim(-5, 5)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()





#KOATERNOIAK

p = bir.quaternion(theta, w1)
q = bir.quaternion(theta2, w2)
s=[]
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

fps = 25
#Irudiak izenez alfabetikoki ordenatu
seq = natsort.natsorted(file_list)
#Irudiak izenez alfabetikoki aldreves ordenatu
seq_ald = natsort.natsorted(file_list, reverse = True)
#Sortu sekuentzia
clip = mpy.ImageSequenceClip(seq+seq_ald, fps=fps)

#Gorde gifa
clip.write_gif('animazioa.gif')
