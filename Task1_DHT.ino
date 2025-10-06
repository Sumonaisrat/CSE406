#include <DHT.h>

// Pin and sensor type definitions
#define DHTPIN 2           
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE); 

float tempThreshold = 20.0; 

void setup() {
  Serial.begin(9600);   
  dht.begin();         
}

void loop() {
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = (tempC * 9.0 / 5.0) + 32; 
  
  // Handle failed sensor readings
  if (isnan(tempC) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(tempC, 2);
  Serial.print(" *C / ");
  Serial.print(tempF, 2);
  Serial.print(" *F");

  if (tempC > tempThreshold) {
    Serial.println(" *** TEMPERATURE ALERT! ***");
  } else {
    Serial.println();
  }

  delay(1000); 
}
