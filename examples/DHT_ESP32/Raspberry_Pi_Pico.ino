// - Lien vidéo: https://youtu.be/Hndon1lIXL0
// - DHT11 DHT22 Library: https://github.com/3tawi/EspDHT
// - Getting Started Raspberry Pi Pico : https://youtu.be/KiM6-Hmxf3s
// - Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects

#include "EspDHT.h"

EspDHT dht;

void setup()
{
  Serial.begin(112500);
  Serial.println();
  dht.setup(28, EspDHT::DHT11); // data pin GP28
  // dht.setup(28, EspDHT::DHT22); // data pin GP28
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
