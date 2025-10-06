/*
  CSE406 - Lab Assignment 02: Task 1
  Maps raw sensor values to percentage and visualizes both
*/

const int sensorPin = A0;

// Calibration values (adjust these based on your sensor)
const int dryValue = 0;      // Raw value when sensor is dry
const int wetValue = 700;    // Raw value when sensor is fully submerged

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the sensor
  int sensorValue = analogRead(sensorPin);
  
  // Map the raw value to percentage (0-100%)
  int waterLevelPercent = map(sensorValue, dryValue, wetValue, 0, 100);
  
  // Constrain the percentage to 0-100 range
  waterLevelPercent = constrain(waterLevelPercent, 0, 100);
  
  // Print both values separated by space for Serial Plotter
  Serial.print(sensorValue);
  Serial.print(" ");
  Serial.println(waterLevelPercent);
  
  delay(100);
}