import numpy as np
import matplotlib.pyplot as plt

data = [[60 , 60.00 , 0.14 , 3.97 , -1.00 , 1.00],
        [50, 49.94 , 0.28 , 3.40 , -0.94 , 1.06],
        [40, 39.80 , 0.41 , 1.96 , -39.80 , 0.20],
        [30, 29.90 , 0.30 , 2.25 , -0.90 , 0.10],
        [20, 20.85 , 0.36 , 1.73 , -0.85 , 0.15],
        [15 , 15.39 , 0.51 , 1.43 , -1.39 , 0.61],
        [10, 8.94 , 0.24 , 1.05 , -0.94 , 0.06],
        [5, 4.57 , 0.82 , 0.81 , -1.57 , 1.43]]
data = np.array(data)

x = data[:,0]
mean = data[:,1]
std = data[:,2]
ms = data[:,3]

plt.subplot(121)
plt.plot(x, mean)
plt.xlabel('Actual distance (cm)')
plt.ylabel('Measured distance (cm)')
plt.grid(True)

plt.subplot(122)
plt.plot(x, ms)
plt.xlabel('Actual distance (cm)')
plt.ylabel('Measurement duration (ms)')
plt.grid(True)

plt.show()
