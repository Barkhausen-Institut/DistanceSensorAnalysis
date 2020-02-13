#include <NewPing.h>

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 80 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  unsigned int sum_cm = 0;
  unsigned int errors = 0;
  const int NUM_MEASUREMENTS = 50;

  auto time = millis();
  for (int i = 0; i < NUM_MEASUREMENTS; i++) {
    int cm = sonar.ping_cm();
    if (cm == 0)
      errors++;
    else
      sum_cm += cm;
  }
  auto dur = millis() - time;

  Serial.print("Errors: "); Serial.println(errors);
  Serial.print("ms overall duration: ");
  Serial.println(dur);
  Serial.print("ms per Measurement: ");
  Serial.println(1.0f * dur / NUM_MEASUREMENTS);
  Serial.print("cm : ");
  Serial.println(1.0f * sum_cm / (NUM_MEASUREMENTS - errors));

  delay(50);
}
