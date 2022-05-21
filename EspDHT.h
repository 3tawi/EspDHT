/******************************************************************
  DHT Temperature & Humidity Sensor library for Arduino.
  Features:
  - Support for DHT11 and DHT22/AM2302/RHT03
  - Very low memory footprint
  - Very small code

  http://www.github.com/3tawi/EspDHT

  Written by Mark Ruys, mark@paracas.nl.
  Updated by 3tawi

  GNU General Public License, check LICENSE for more information.
  All text above must be included in any redistribution.

  Datasheets:
  - http://www.micro4you.com/files/sensor/DHT11.pdf
  - http://www.adafruit.com/datasheets/DHT22.pdf
  - http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Sensors/Weather/RHT03.pdf
  - http://meteobox.tk/files/AM2302.pdf

******************************************************************/
#ifndef EspDHT_h
#define EspDHT_h
#include <Arduino.h>

class EspDHT
{
public:
  typedef enum {
    DHT11,
    DHT22
  }
  DHT_MODEL;

  void readSensor();
  void setup(uint8_t pin, DHT_MODEL model);
  float getTemperature() { return temperature; };
  float getHumidity() { return humidity; }
protected:
  float temperature;
  float humidity;
  uint8_t pin;
  DHT_MODEL model;
private:
  unsigned long lastReadTime;
  void resetTimer();
};

#endif
