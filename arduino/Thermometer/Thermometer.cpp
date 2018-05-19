#include "Thermometer.h"

Thermometer::Thermometer(uint8_t pin, void (*onTemperature)(double temperature)): oneWire(pin), sensors(&oneWire), onTemperature(onTemperature) {
  pinMode(pin, INPUT_PULLUP); 
}

void Thermometer::start(bool debug) {
  sensors.begin();
}

void Thermometer::poll() {
  sensors.requestTemperatures();
  double observation = sensors.getTempCByIndex(0);
  Serial.println("observation: ");
  Serial.println(observation);
  onTemperature(observation);
}

