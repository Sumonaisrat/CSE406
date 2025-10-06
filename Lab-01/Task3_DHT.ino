#include <DHT.h>

// Pin and sensor type definitions
#define DHTPIN 2            // Pin connected to the DHT sensor
#define DHTTYPE DHT11       // Define DHT 22 (or DHT11)

DHT dht(DHTPIN, DHTTYPE); // Initialize the DHT sensor

// Moving Average variables
const int NUM_SAMPLES = 10;  // Number of samples for moving average
float readings[NUM_SAMPLES];  // Array to store temperature readings
int readIndex = 0;            // Current index for storing readings
float total = 0;              // Sum of the last NUM_SAMPLES readings
float average = 0;            // Averaged temperature

void setup() {
  Serial.begin(9600);   // Start serial communication
  dht.begin();          // Initialize the DHT sensor
  
  // Initialize all readings to 0
  for (int i = 0; i < NUM_SAMPLES; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // Read temperature and humidity from the DHT sensor
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature(); // Celsius
  float tempF = (tempC * 9.0 / 5.0) + 32; // Convert to Fahrenheit
  
  // Handle failed sensor readings
  if (isnan(tempC) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Update the moving average with the new reading
  total -= readings[readIndex];
  readings[readIndex] = tempC;  // Store the new temperature reading
  total += readings[readIndex];
  readIndex = (readIndex + 1) % NUM_SAMPLES;  // Circular index for the array
  
  // Calculate the moving average of the last NUM_SAMPLES readings
  average = total / NUM_SAMPLES;

  // Print raw and filtered temperature data
  Serial.print("Raw Temp: ");
  Serial.print(tempC, 2);
  Serial.print(" *C, Filtered Temp: ");
  Serial.print(average, 2);
  Serial.print(" *C / ");
  Serial.print(tempF, 2);
  Serial.print(" *F");

  Serial.println();
  
  delay(1000);  // Delay for 1 second before the next reading
}
