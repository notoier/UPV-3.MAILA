
# 3d kurbaren ikuspegiekin animazioa

import mpl_toolkits.mplot3d
import numpy as np
from math import pi
import matplotlib.pyplot as plt

theta = np.linspace(-4 * pi, 4 * pi, 100)
z = np.linspace(-2, 2, 100)
r = z**2 + 1.
x = r * np.sin(theta)
y = r * np.cos(theta)

fig = plt.figure()
ax = fig.gca(projection='3d')

ax.plot(x, y, z)

ax.set_xlim(-5, 5)      
ax.set_ylim(-5, 5)
ax.set_zlim(-2, 2)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# ikuspegi estatikoa
# plt.show()

# animazioa ikuspegi desberdinekin
for angle in range(0, 360):
    ax.view_init(30, angle)
    plt.draw()
    plt.pause(.01)

