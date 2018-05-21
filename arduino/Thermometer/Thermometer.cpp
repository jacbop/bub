#include "Thermometer.h"
#include "Timing.h"

Timing timing;

Thermometer::Thermometer(uint8_t pin, uint samplePeriod, void (*onTemperature)(double temperature)):
  oneWire(pin), sensors(&oneWire), samplePeriod(samplePeriod), lastSample(0), onTemperature(onTemperature) {
  pinMode(pin, INPUT_PULLUP);
}

void Thermometer::start(bool debug) {
  sensors.begin();

  DeviceAddress insideThermometer;

  // look for sensors
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  if (!sensors.getAddress(insideThermometer, 0)) {
    Serial.println("Unable to find address for Device 0");
  }

  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  sensors.setResolution(insideThermometer, 9);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC);
  Serial.println();
}

void Thermometer::poll(long now) {
  if (timing.hadElapsed(lastSample, now, samplePeriod)) {
    lastSample = now;
    sensors.requestTemperatures();
    double observation = sensors.getTempCByIndex(0);
    onTemperature(observation);
  }
}

// function to print a device address
void Thermometer::printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


