#include <DHT.h>

// Pin and sensor type definitions
#define DHTPIN 2            // Pin connected to the DHT sensor
#define DHTTYPE DHT11       // Define DHT 22 (or DHT11)

DHT dht(DHTPIN, DHTTYPE); // Initialize the DHT sensor

// Temperature threshold variable
float tempThreshold = 20.0;  // Set threshold temperature (Celsius)

void setup() {
  Serial.begin(9600);   // Start serial communication
  dht.begin();          // Initialize the DHT sensor
  Serial.println("Enter temperature threshold in the format T<value> (e.g., T25 for 25°C)");
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

  // Print current temperature
  Serial.print("Temp: ");
  Serial.print(tempC, 2);
  Serial.print(" *C / ");
  Serial.print(tempF, 2);
  Serial.print(" *F");

  // If temperature exceeds the threshold, print an alert
  if (tempC > tempThreshold) {
    Serial.println(" *** TEMPERATURE ALERT! ***");
  } else {
    Serial.println();
  }

  // Check for serial input to change the temperature threshold
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    if (input.startsWith("T")) {
      float newThreshold = input.substring(1).toFloat();
      tempThreshold = newThreshold;
      Serial.print("New temperature threshold set to: ");
      Serial.println(tempThreshold);
    }
  }

  delay(1000);  // Delay for 1 second before the next reading
}
