import mpl_toolkits.mplot3d
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import splprep, splev, BSpline

puntuak = np.array([[1, 1, 2], [2, 2, 3], [3, 3, 3], [3, 4, 3], [3, 4, 5]]).T
basis_splinea, t_puntuak = splprep(puntuak, k=3, s=0)   # spline kubikoa, leuntasuna s=0 eta s=1 hartu
print(basis_splinea[2])
print(basis_splinea[0])
print(basis_splinea[1][0])
print(basis_splinea[1][1])
print(basis_splinea[1][2])
t_kurba = np.linspace(0, 1, 100)   # orain [0, 1] tartea
bs_kurba = splev(t_kurba, basis_splinea)

f0 = BSpline(basis_splinea[0], np.array([1,0,0,0,0]), 3)
plt.plot(t_kurba,f0(t_kurba))

fig = plt.figure()
#ax = fig.gca(projection='3d')
ax = fig.add_subplot(projection='3d')

ax.plot(puntuak[0,:], puntuak[1,:], puntuak[2,:], 'ro')
ax.plot(bs_kurba[0], bs_kurba[1], bs_kurba[2], 'b-')

ax.set_xlim(0, 5)
ax.set_ylim(0, 5)
ax.set_zlim(0, 5)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

#TRANSBORDADOREA
#Splinen puntuak
puntuakGoikoak = np.array([[0, 0, 0],[0, 0.2, 0.4], [0, 1.5, 0.8], [0, 4, 1], [0, 5, 2], [0, 5, 0]]).T
puntuakBehekoak1 = np.array([[0, 0, 0],[0.1, 0.05, 0], [0.6, 0.8, 0], [0.9, 3.2, 0], [1.6, 4.5, 0],[0, 5, 0]]).T
puntuakBehekoak2 = np.array([[0, 0, 0],[-0.1, 0.05, 0], [-0.6, 0.8, 0], [-0.9, 3.2, 0], [-1.6, 4.5, 0],[0, 5, 0]]).T


#Definitu splineak
basis_splineaGoikoa, t_puntuakGoikoa = splprep(puntuakGoikoak, k=3, s=0)   # spline kubikoa, leuntasuna s=0 eta s=1 hartu
basis_splineaBehekoa1, t_puntuakBehekoa1 = splprep(puntuakBehekoak1, k=3, s=0)   # spline kubikoa, leuntasuna s=0 eta s=1 hartu
basis_splineaBehekoa2, t_puntuakBehekoa2 = splprep(puntuakBehekoak2, k=3, s=0)   # spline kubikoa, leuntasuna s=0 eta s=1 hartu


#Kurbak sortu
t_kurba = np.linspace(0, 1, 100)   # orain [0, 1] tartea

bs_kurbaGoikoa = splev(t_kurba, basis_splineaGoikoa)
bs_kurbaBehekoa1 = splev(t_kurba, basis_splineaBehekoa1)
bs_kurbaBehekoa2 = splev(t_kurba, basis_splineaBehekoa2)

fig = plt.figure()
#ax = fig.gca(projection='3d')
ax = fig.add_subplot(projection='3d')

#GRAFIKATU
#ax.plot(puntuakGoikoak[0,:], puntuakGoikoak[1,:], puntuakGoikoak[2,:], 'ro')
ax.plot(bs_kurbaGoikoa[0], bs_kurbaGoikoa[1], bs_kurbaGoikoa[2], 'b-')

#ax.plot(puntuakBehekoak1[0,:], puntuakBehekoak1[1,:], puntuakBehekoak1[2,:], 'ro')
ax.plot(bs_kurbaBehekoa1[0], bs_kurbaBehekoa1[1], bs_kurbaBehekoa1[2], 'b-')

#ax.plot(puntuakBehekoak2[0,:], puntuakBehekoak2[1,:], puntuakBehekoak2[2,:], 'ro')
ax.plot(bs_kurbaBehekoa2[0], bs_kurbaBehekoa2[1], bs_kurbaBehekoa2[2], 'b-')

# Grafikoaren tamaina
ax.set_xlim(-3.5, 3.5)
ax.set_ylim(-1, 7)
ax.set_zlim(-2, 3.5)
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