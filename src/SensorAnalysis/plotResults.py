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

data_vl53l1x = [[60 , 53.32 , 0.47 , 18.51 , -0.32 , 0.68 ],
                [50 , 48.12 , 0.33 , 18.56 , -0.12 , 0.88 ],
                [40 , 39.02 , 0.14 , 18.45 , -0.02 , 0.98 ],
                [30 , 29.11 , 0.31 , 18.42 , -0.11 , 0.89 ],
                [20 , 20.35 , 0.48 , 18.55 , -0.35 , 0.65 ],
                [15 , 15.20 , 0.40 , 18.54 , -0.20 , 0.80 ],
                [10 , 10.60 , 0.49 , 18.58 , -0.60 , 0.40 ],
                [5 , 4.11 , 0.31 , 18.43 , -0.11 , 0.89 ]]

data = np.array(data_vl53l1x)

def plot(data, label):

    x = data[:,0]
    mean = data[:,1]
    std = data[:,2]
    ms = data[:,3]

    plt.subplot(121)
    plt.plot(x, mean, label=label)
    plt.xlabel('Actual distance (cm)')
    plt.ylabel('Measured distance (cm)')
    plt.legend()
    plt.grid(True)

    plt.subplot(122)
    plt.plot(x, ms, label=label)
    plt.xlabel('Actual distance (cm)')
    plt.ylabel('Measurement duration (ms)')
    plt.legend()
    plt.grid(True)

plt.subplot(121)
plt.plot([0, 60], [0, 60], 'k--')

plot(np.array(data_hc04), "SR-HC04")
plot(np.array(data_vl53l0x), "VL53L0X")
plot(np.array(data_vl53l1x), "VL53L1X")
plt.subplot(121)
plt.show()
