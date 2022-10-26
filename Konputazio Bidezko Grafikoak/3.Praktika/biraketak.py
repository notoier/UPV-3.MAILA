
from math import sqrt, sin, cos, acos, pi
import numpy as np

def rodrigues(theta_rad, bektorea):           # Rodrigues-en formularekin biraketa matrizea
    array1d = np.array(bektorea)                                # zerrenda sartuko balitz egokitzeko 
    w = array1d / sqrt(np.sum(array1d**2))                                  # w unitarioa izateko
    J = np.array( [[0,-w[2],w[1]], [w[2],0,-w[0]], [-w[1],w[0],0]] )
    I = np.eye(3)
    return I + sin(theta_rad) * J + (1 - cos(theta_rad)) * np.dot(J,J)     


def quaternion(theta_rad, bektorea):                   # koaternoia sortzeko
    array1d = np.array(bektorea)
    w = array1d / sqrt(np.sum(array1d**2))
    return np.hstack((cos(theta_rad/2.), sin(theta_rad/2.) * w))


def quat_dot_quat(p, q):   # bi koaternoi biderkatu, bat matrizea izan daiteke
    return np.array( [p[0]*q[0] - p[1]*q[1] - p[2]*q[2] - p[3]*q[3],
                      p[0]*q[1] + p[1]*q[0] + p[2]*q[3] - p[3]*q[2], 
                      p[0]*q[2] - p[1]*q[3] + p[2]*q[0] + p[3]*q[1], 
                      p[0]*q[3] + p[1]*q[2] - p[2]*q[1] + p[3]*q[0]] )


def quat_dot_curve(q, kurba):           # koaternoia eta 3d kurba (ndarray edo list) biderkatzeko
    qinv = q * np.array( [1,-1,-1,-1] )                   
    kurba4d = np.row_stack((np.zeros(len(kurba[0])), kurba)) 
    return quat_dot_quat(quat_dot_quat(q, kurba4d), qinv)[1:] # kurbako puntuak biratuta q-ren bidez


def SLInterp(p, q, t):         # Spherical Linear Interpolation: bi koaternoi eta 0<=t<=1
    theta = acos(np.dot(p, q))
    slerp_nn = sin((1 - t) * theta) * p + sin(t * theta) * q      
    return slerp_nn / sqrt(np.sum(slerp_nn**2))          # Spherical Linear intERPolation koaternoia

