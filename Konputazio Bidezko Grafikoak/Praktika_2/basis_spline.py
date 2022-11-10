
import mpl_toolkits.mplot3d
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import splprep, splev, BSpline

puntuak = np.array([[1, 1, 2], [2, 2, 3], [3, 3, 3], [3, 4, 3], [3, 4, 5]]).T
basis_splinea, t_puntuak = splprep(puntuak, k=3, s=0)   # spline kubikoa, leuntasuna s=0 eta s=1 hartu
t_kurba = np.linspace(0, 1, 100)   # orain [0, 1] tartea
bs_kurba = splev(t_kurba, basis_splinea)

fig = plt.figure()
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


