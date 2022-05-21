/******************************************************************
  DHT Temperature & Humidity Sensor library for Arduino.
  Features:
  - Support for DHT11 and DHT22/AM2302/RHT03
  - Auto detect sensor model
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

#include "EspDHT.h"

void EspDHT::setup(uint8_t pin, DHT_MODEL model)
{
  EspDHT::pin = pin;
  EspDHT::model = model;
  EspDHT::resetTimer();
}

void EspDHT::resetTimer()
{
  lastReadTime = millis() - 3000;
}

void EspDHT::readSensor()
{
  unsigned long startTime = millis();
  if ( (unsigned long)(startTime - lastReadTime) < (model == DHT11 ? 999L : 1999L) ) {
    return;
  }
  lastReadTime = startTime;
  temperature = NAN;
  humidity = NAN;
  uint16_t rawHumidity = 0;
  uint16_t rawTemperature = 0;
  uint16_t data = 0;
  // Request sample
  digitalWrite(pin, LOW); // Send start signal
  pinMode(pin, OUTPUT);
  if ( model == DHT11 ) { delay(18); }
  else { delayMicroseconds(800); }
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH); // Switch bus to receive data

  noInterrupts();
  for ( int8_t i = -3 ; i < 2 * 40; i++ ) {
    byte age;
    startTime = micros();

    do {
      age = (unsigned long)(micros() - startTime);
      if ( age > 90 ) {
        interrupts();
        return;
      }
    }
    while ( digitalRead(pin) == (i & 1) ? HIGH : LOW );

    if ( i >= 0 && (i & 1) ) {
      // Now we are being fed our 40 bits
      data <<= 1;

      // A zero max 30 usecs, a one at least 68 usecs.
      if ( age > 30 ) {
        data |= 1; // we got a one
      }
    }

    switch ( i ) {
      case 31:
        rawHumidity = data;
        break;
      case 63:
        rawTemperature = data;
        data = 0;
        break;
    }
  }

  interrupts();

  // Verify checksum

  if ( (byte)(((byte)rawHumidity) + (rawHumidity >> 8) + ((byte)rawTemperature) + (rawTemperature >> 8)) != data ) {
    return;
  }

  // Store readings

  if ( model == DHT11 ) {
    humidity = rawHumidity >> 8;
    temperature = rawTemperature >> 8;
    if ( humidity > 90 || humidity < 20 || temperature > 50 || temperature < 0) {
      temperature = NAN;
      humidity = NAN;
    }
  } else {
    humidity = rawHumidity * 0.1;
    if ( rawTemperature & 0x8000 ) {
      rawTemperature = -(int16_t)(rawTemperature & 0x7FFF);
    }
    temperature = ((int16_t)rawTemperature) * 0.1;
    if ( humidity > 100 || humidity < 0 || temperature > 125 || temperature < -40) {
      temperature = NAN;
      humidity = NAN;
    }
  }
}
