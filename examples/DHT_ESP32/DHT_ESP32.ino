#include "EspDHT.h"

EspDHT dht;

void setup()
{
  Serial.begin(112500);
  Serial.println();
  dht.setup(2, EspDHT::DHT11); // data pin 2
}

void loop()
{
  delay(3000);
  dht.readSensor();
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  if (isnan(temperature) || isnan(humidity)) {
    return;
  }
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.print(" °C Humidity : ");
  Serial.print(humidity);
  Serial.println(" %");
}