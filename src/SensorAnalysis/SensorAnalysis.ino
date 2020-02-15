#include <Wire.h>

#include "NewPing.h"
#include "VL53L0X.h"
#include "VL53L1X.h"

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
VL53L0X vl53l0x;
VL53L1X vl53l1x;

enum class SensorType {
  HC04 = 0,
  VL53L0X = 1,
  VL53L1X = 2,
};

const SensorType SensorToUse = SensorType::VL53L1X;

struct MeasurementResult {
  float mean;
  float std;
  int numErrors;
  float deltaMin;
  float deltaMax;
  float avgDuration;
};

const int NUM_MEASUREMENTS = 100;
float measurements[NUM_MEASUREMENTS];

float min_element(const float* begin, const int num_elem) {
  float min = 9999999;
  for (int i = 0; i < num_elem; i++) {
    if (begin[i] < min)
      min = begin[i];
  }
  return min;
}

float max_element(const float* begin, const int num_elem) {
  float max = -9999999;
  for (int i = 0; i < num_elem; i++) {
    if (begin[i] > max)
      max = begin[i];
  }
  return max;
}

template <class F>
void doMeasurement(F f, MeasurementResult& m) {
  float measurements[NUM_MEASUREMENTS];

  auto start = millis();
  for(int i = 0; i < NUM_MEASUREMENTS; i++) {
    measurements[i] = f();
  }
  auto dur = millis() - start;
  m.avgDuration = 1.0f * dur / NUM_MEASUREMENTS;

  m.numErrors = 0;
  m.mean = 0;
  for (int i = 0; i < NUM_MEASUREMENTS; i++) {
    m.mean += measurements[i];
    if (measurements[i] == 0)
      m.numErrors++;
  }
  m.mean /= (NUM_MEASUREMENTS - m.numErrors);

  m.std = 0;
  for(int i = 0; i < NUM_MEASUREMENTS; i++) {
    if (measurements[i] != 0) {
      float d = measurements[i] - m.mean;
      m.std += d*d;
    }
  }
  m.std /= (NUM_MEASUREMENTS-1 - m.numErrors);
  m.std = sqrtf(m.std);

  m.deltaMin = min_element(measurements, NUM_MEASUREMENTS) - m.mean;
  m.deltaMax = max_element(measurements, NUM_MEASUREMENTS) - m.mean;
}

void showMeasurement(const MeasurementResult& m) {
  Serial.print("ms per Measurement     : ");  Serial.println(m.avgDuration);
  Serial.print("Distance measured  (cm): ");  Serial.println(m.mean);
  Serial.print("Standard deviation (cm): ");  Serial.println(m.std);
  Serial.print("deltaMin           (cm): ");  Serial.println(m.deltaMin);
  Serial.print("deltaMax           (cm): ");  Serial.println(m.deltaMax);
  Serial.print("num Errors             : ");  Serial.println(m.numErrors);
  printTableLine(m);
}

void printTableLine(const MeasurementResult& m) {
  Serial.print(" | "); Serial.print(m.mean);
  Serial.print(" | "); Serial.print(m.std);
  Serial.print(" | "); Serial.print(m.avgDuration);
  Serial.print(" | "); Serial.print(m.deltaMin);
  Serial.print(" | "); Serial.print(m.deltaMax);
  Serial.print(" | "); Serial.println();
}

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  Wire.begin();
  Wire.setClock(400000);
  if (SensorToUse == SensorType::VL53L0X) {
    vl53l0x.setTimeout(500);
    if(!vl53l0x.init()) {
      Serial.println("Failed to detect and initialize sensor!");
      while (true) {}
    }
    vl53l0x.startContinuous();
  }
  else if (SensorToUse == SensorType::VL53L1X) {
    vl53l1x.setTimeout(500);
    if(!vl53l1x.init()) {
      Serial.println("Failed to detect and initialize VL53L1X");
      while (true) {}
    }
    vl53l1x.setDistanceMode(VL53L1X::Short);
    vl53l1x.setMeasurementTimingBudget(10000);

    // Start continuous readings at a rate of one measurement every 50 ms (the
    // inter-measurement period). This period should be at least as long as the
    // timing budget.
    vl53l1x.startContinuous(10);
  }

  delay(500);

}

void loop() {

  Serial.setTimeout(100000);
  const int act_dist[] = {60, 50, 40, 30, 20, 15, 10, 5};
  const int NUM_DISTS = sizeof(act_dist)/sizeof(act_dist[0]);
  MeasurementResult results[NUM_DISTS];
  for(int i = 0; i < NUM_DISTS; i++) {
    Serial.print("Set distance to "); Serial.print(act_dist[i]); Serial.println(" cm...");
    Serial.readStringUntil('\n');
    Serial.println("Measuring...");

    MeasurementResult result;
    if (SensorToUse == SensorType::HC04)
      doMeasurement([](){return sonar.ping_cm(); }, result);
    else if (SensorToUse == SensorType::VL53L0X)
      doMeasurement([](){
	  float v = vl53l0x.readRangeContinuousMillimeters() / 10;
	  if (vl53l0x.timeoutOccurred())
	    return 0.0f;
	  else return v;
	}, result);
    else if (SensorToUse == SensorType::VL53L1X) {
      doMeasurement([](){
	  float v = vl53l1x.read() / 10;
	  if (vl53l1x.timeoutOccurred())
	    return 0.0f;
	  else return v;
	}, result);
    }
    else
      Serial.println("ERROR in sensor choice!");

    Serial.println("=============================");
    showMeasurement(result);

    results[i] = result;
  }

  Serial.println("Summary:");
  for(int i = 0; i < NUM_DISTS; i++) {
    Serial.print("| ");
    Serial.print(act_dist[i]);
    printTableLine(results[i]);
  }



  delay(50);
}
