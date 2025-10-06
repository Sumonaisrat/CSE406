/*
  CSE406 - Lab Assignment 02: Task 2
  Implements water level alarm system with threshold detection
*/

const int sensorPin = A0;

// Calibration values
const int dryValue = 0;
const int wetValue = 700;

// Threshold definitions
const int LOW_LEVEL = 25;
const int MEDIUM_LEVEL = 75;
const int HIGH_LEVEL = 95;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read and map sensor value
  int sensorValue = analogRead(sensorPin);
  int waterLevelPercent = map(sensorValue, dryValue, wetValue, 0, 100);
  waterLevelPercent = constrain(waterLevelPercent, 0, 100);
  
  // Display current readings
  Serial.print("Raw Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Water Level: ");
  Serial.print(waterLevelPercent);
  Serial.print("%");
  
  // Check thresholds and trigger alarms
  if (waterLevelPercent >= HIGH_LEVEL) {
    Serial.println(" | ALERT: HIGH WATER LEVEL! Critical!");
  } 
  else if (waterLevelPercent >= MEDIUM_LEVEL) {
    Serial.println(" | WARNING: Medium water level detected");
  } 
  else if (waterLevelPercent >= LOW_LEVEL) {
    Serial.println(" | INFO: Low water level");
  } 
  else {
    Serial.println(" | STATUS: Water level very low");
  }
  
  delay(100);
}