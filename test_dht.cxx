#include <Arduino.h>
#include <DHT.h>

// What pin to connect the sensor to
#define DHT_PIN 9 
 
DHT dht = DHT(DHT_PIN, DHT11);

 
void setup(void) {
  Serial.begin(9600);

  dht.readTemperature();
}
 
void loop(void) {
  float reading = dht.readTemperature(true);
 
  Serial.print("DHT reading "); 
  Serial.print(reading);
  Serial.println("f");
 
  delay(1000);
}