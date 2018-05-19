// Basic operation of rotary encoder controlling OLED with Wifi and thermometer

#include "Thermometer.h"
#include "Setpoint.h"
#include "Display.h"
#include "Wifi.h"

Wifi wifi;
Display display;

void onTemperature(double temperature) {
  display.setTemperature(temperature);
}

void onValue(double value) {
  display.setValue(value);
}

void onSetpoint(double setpoint) {
  display.setSetpoint(setpoint);
}

Thermometer thermometer(D3, 5000, onTemperature);
Setpoint setpoint(D5, D6, D7, 10.0, 80.0, 22.0, 3000, onSetpoint, onValue);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder + OLED + Wifi + Thermometer Test:");
  wifi.start(false);
  display.start(false);
  thermometer.start(false);
  setpoint.start(false);
}

void loop() {
  long now = millis();
  setpoint.poll(now);
  thermometer.poll(now);
}


