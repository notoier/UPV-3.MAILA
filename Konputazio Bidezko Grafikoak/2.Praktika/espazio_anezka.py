import numpy as np
import matplotlib.pyplot as plt
import biraketa.py 
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
bs_kurba4 = splev(t_kurba, basis_splinea4)
bs_kurba5 = splev(t_kurba, basis_splinea5)


fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.plot(kurba_puntuak[0,:], kurba_puntuak[1,:], kurba_puntuak[2,:], 'ro')

ax.plot(bs_kurba[0], bs_kurba[1], bs_kurba[2], 'b-')
ax.plot(bs_kurba2[0], bs_kurba2[1], bs_kurba2[2], 'b-')
ax.plot(bs_kurba3[0], bs_kurba3[1], bs_kurba3[2], 'b-')
ax.plot(bs_kurba4[0], bs_kurba4[1], bs_kurba4[2], 'b-')
ax.plot(bs_kurba5[0], bs_kurba5[1], bs_kurba5[2], 'b-')



ax.set_xlim(0, 5)      
ax.set_ylim(0, 5)
ax.set_zlim(0, 5)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

#(4.5,2.5,1)
#(2,2.5,1.5)
#(0.5,2.5,3)
#(o.5,2.5,1)