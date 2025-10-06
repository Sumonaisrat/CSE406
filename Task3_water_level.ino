/*
  CSE406 - Lab Assignment 02: Task 3
  Calculates and plots rate of change in water level
*/

const int sensorPin = A0;

// Calibration values
const int dryValue = 0;
const int wetValue = 700;

// Variable to store previous reading
int previousLevel = 0;
bool firstReading = true;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read and map sensor value
  int sensorValue = analogRead(sensorPin);
  int currentLevel = map(sensorValue, dryValue, wetValue, 0, 100);
  currentLevel = constrain(currentLevel, 0, 100);
  
  // Calculate rate of change
  int rateOfChange = 0;
  
  if (firstReading) {
    // First iteration - no previous value to compare
    previousLevel = currentLevel;
    firstReading = false;
  } else {
    // Calculate difference from previous reading
    rateOfChange = currentLevel - previousLevel;
  }
  
  // Print current level and rate of change for Serial Plotter
  Serial.print(currentLevel);
  Serial.print(" ");
  Serial.println(rateOfChange);
  
  // Update previous level for next iteration
  previousLevel = currentLevel;
  
  delay(100);
}