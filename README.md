# Evaluation of diverse distance sensors

This repository contains evaluation of processing time and measurement accuracy of different distance sensors. Currently, the following sensors are investigated:

- Ultrasonic Sensor HC-SR04 using the [NewPing library](https://github.com/microflo/NewPing)
- Time-Of-Flight Sensor VL53L0X using the appropriate [Pololu Arduino Library](https://github.com/pololu/vl53l0x-arduino)
- Time-Of-Flight Sensor VL53L1X using the appropriate [Pololu Arduino Library](https://github.com/pololu/vl53l1x-arduino)


## Build and Run
The source code for the different libraries is already cloned into this repository. Hence, no external libraries need to be installed. The program was tested on an Arduino Leonardo.

- Connect the `TRIGGER_PIN` and `ECHO_PIN` to the HC-SR04 sensor.
- Connect I2C SCL and SDL pins to the according sensor pins. **In our tests, the program did not work when both sensors were connected at the same time.**
- Open Arduino IDE, compile and upload `src/SensorAnalysis/SensorAnalysis.ino`.
- Open the serial monitor. Upon running. the program asks you to set the real distance between sensor and object to a given value. After pressing `RETURN` the measurement process starts. After finishing all measurements, the a summary similar as follows is written to the Serial Monitor:

```
ms per Measurement     : 3.97
Distance measured  (cm): 60.00
Standard deviation (cm): 0.14
deltaMin           (cm): -1.00
deltaMax           (cm): 1.00
num Errors             : 0
 | 60.00 | 0.14 | 3.97 | -1.00 | 1.00 |
```
