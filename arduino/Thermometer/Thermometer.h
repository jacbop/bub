#ifndef HEADER_THERMOMETER
#define HEADER_THERMOMETER

#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// https://github.com/adafruit/MAX31850_OneWire
// https://github.com/adafruit/MAX31850_DallasTemp

class Thermometer {
  private:
    OneWire oneWire;
    DallasTemperature sensors;
    void (*onTemperature)(double temperature);
    
  public:
    Thermometer(uint8_t pin, void (*onTemperature)(double temperature));
    void start(bool debug);
    void poll();
};

#endif