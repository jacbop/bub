#include "Thermometer.h"

int sample = 0;

void onTemperature(double temperature) {
  Serial.print(sample++);
  Serial.print(": temperature: ");
  Serial.print(temperature);
  Serial.println("C");
}

Thermometer thermometer(D3, 10000, onTemperature);

void setup()
{
  Serial.begin(115200);
  Serial.println("DS18B20 with OneWire test:");
  thermometer.start(false);
}

void loop()
{
  long now = millis();
  thermometer.poll(now);
}
