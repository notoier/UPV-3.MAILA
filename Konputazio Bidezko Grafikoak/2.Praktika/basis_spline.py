
import mpl_toolkits.mplot3d
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import splprep, splev, BSpline

puntuak = np.array([[1, 1, 2], [2, 2, 3], [3, 3, 3], [3, 4, 3], [3, 4, 5]]).T
basis_splinea, t_puntuak = splprep(puntuak, k=3, s=0)   # spline kubikoa, leuntasuna s=0 eta s=1 hartu
t_kurba = np.linspace(0, 1, 100)   # orain [0, 1] tartea
bs_kurba = splev(t_kurba, basis_splinea)

f0 = BSpline(basis_splinea[0], np.array([1,0,0,0,0]), 3)
plt.plot(t_kurba,f0(t_kurba))

fig = plt.figure()
ax = fig.gca(projection='3d')

ax.plot(puntuak[0,:], puntuak[1,:], puntuak[2,:], 'ro')
ax.plot(bs_kurba[0], bs_kurba[1], bs_kurba[2], 'b-')

ax.set_xlim(0, 5)      
ax.set_ylim(0, 5)
ax.set_zlim(0, 5)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

#Transbordadorea sortu
goikoP = np.array([[0, 0, 0],[0, 0.2, 0.4], [0, 1.5, 0.8], [0, 4, 1], [0, 5, 2], [0, 5, 0]]).T
behekoP1 = np.array([[0, 0, 0],[0.1, 0.05, 0], [0.6, 0.8, 0], [0.9, 3.2, 0], [1.6, 4.5, 0],[0, 5, 0]]).T
behekoP2 = np.array([[0, 0, 0],[-0.1, 0.05, 0], [-0.6, 0.8, 0], [-0.9, 3.2, 0], [-1.6, 4.5, 0],[0, 5, 0]]).T


#Splineak definitu
basis_splineaG, t_goikoP = splprep(goikoP, k=3, s=0)   # spline kubikoa, leuntasuna s=0 eta s=1 hartu
basis_splineaB1, t_behekoP1 = splprep(behekoP1, k=3, s=0)   # spline kubikoa, leuntasuna s=0 eta s=1 hartu
basis_splineaB2, t_behekoP2 = splprep(behekoP2, k=3, s=0)   # spline kubikoa, leuntasuna s=0 eta s=1 hartu


#Kurbak sortu
t_kurba = np.linspace(0, 1, 100)

bs_kurbaGoikoa = splev(t_kurba, basis_splineaG)
bs_kurbaBehekoa1 = splev(t_kurba, basis_splineaB1)
bs_kurbaBehekoa2 = splev(t_kurba, basis_splineaB2)

fig = plt.figure()
#ax = fig.gca(projection='3d')
ax = fig.add_subplot(projection='3d')

#Kurbak marraztu
ax.plot(bs_kurbaGoikoa[0], bs_kurbaGoikoa[1], bs_kurbaGoikoa[2], 'b-')

ax.plot(bs_kurbaBehekoa1[0], bs_kurbaBehekoa1[1], bs_kurbaBehekoa1[2], 'b-')

ax.plot(bs_kurbaBehekoa2[0], bs_kurbaBehekoa2[1], bs_kurbaBehekoa2[2], 'b-')

# Grafikoaren tamaina definitu
ax.set_xlim(-5, 5)
ax.set_ylim(-1, 10)
ax.set_zlim(-2.5, 5)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

#IKUSPEGI ESTATIKOA
#plt.show()

#IKUSPEGI DINAMIKOA
for angle in range(0, 360):
    ax.view_init(30, angle)
    plt.draw()
    plt.pause(.01)
