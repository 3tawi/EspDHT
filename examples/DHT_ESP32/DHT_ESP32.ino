// - DHT11 DHT22 Library: https://github.com/3tawi/EspDHT
// - Getting Started ESP32 : https://www.youtube.com/watch?v=9b0Txt-yF7E
// - Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects

#include "EspDHT.h"

EspDHT dht;

void setup()
{
  Serial.begin(112500);
  Serial.println();
  dht.setup(2, EspDHT::DHT11); // data pin 2
  // dht.setup(2, EspDHT::DHT22); // data pin 2
}

void loop()
{
  delay(3000);
  dht.readSensor();
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.print(" °C Humidity : ");
  Serial.print(humidity);
  Serial.println(" %");
}