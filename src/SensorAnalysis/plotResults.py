import numpy as np
import matplotlib.pyplot as plt

data_hc04 = [[60 , 60.00 , 0.14 , 3.97 , -1.00 , 1.00],
             [50, 49.94 , 0.28 , 3.40 , -0.94 , 1.06],
             [40, 39.80 , 0.41 , 1.96 , -39.80 , 0.20],
             [30, 29.90 , 0.30 , 2.25 , -0.90 , 0.10],
             [20, 20.85 , 0.36 , 1.73 , -0.85 , 0.15],
             [15 , 15.39 , 0.51 , 1.43 , -1.39 , 0.61],
             [10, 8.94 , 0.24 , 1.05 , -0.94 , 0.06],
             [5, 4.57 , 0.82 , 0.81 , -1.57 , 1.43]]
data_vl53l0x = [[60, 35.06 , 0.34 , 31.33 , -1.06 , 0.94 ],
                [50, 39.48 , 0.50 , 31.36 , -0.48 , 0.52 ],
                [40, 43.93 , 1.05 , 31.33 , -3.93 , 1.07 ],
                [30, 34.01 , 0.10 , 31.33 , -0.01 , 0.99 ],
                [20, 25.12 , 0.33 , 31.33 , -0.12 , 0.88 ],
                [15, 20.91 , 0.29 , 31.32 , -0.91 , 0.09 ],
                [10, 15.17 , 0.51 , 31.25 , -1.17 , 0.83 ],
                [5, 10.01 , 0.10 , 31.19 , -0.01 , 0.99 ]];

data = np.array(data_vl53l0x)

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
