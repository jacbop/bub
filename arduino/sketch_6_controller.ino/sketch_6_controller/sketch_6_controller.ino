// Basic operation of rotary encoder controlling OLED with Wifi and thermometer and controller logic

#include "Controller.h"
#include "Thermometer.h"
#include "Setpoint.h"
#include "Display.h"
#include "Wifi.h"

double defaultSetpoint = 20.0;
double defaultSetpointDifferential = 2.0;

Wifi wifi;
Display display(defaultSetpoint); // D1, D2

void onCool(bool isCalling) {
  display.setCool(isCalling);
}

void onHeat(bool isCalling) {
  display.setHeat(isCalling);
}

Controller controller(D4, D8, defaultSetpointDifferential, defaultSetpoint, onCool, onHeat);

void onTemperature(double temperature) {
  controller.setTemperature(temperature);
  display.setTemperature(temperature);
}

Thermometer thermometer(D3, 5000, onTemperature);

void onValue(double value) {
  display.setValue(value);
}

void onSetpoint(double setpoint) {
  controller.setSetpoint(setpoint);
  display.setSetpoint(setpoint);
}

Setpoint setpoint(D5, D6, D7, 10.0, 80.0, defaultSetpoint, 3000, onSetpoint, onValue);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder + OLED + Wifi + Thermometer + Controller Test:");
  wifi.start(false);
  display.start(false);
  thermometer.start(false);
  setpoint.start(false);
  controller.start(false);
}

void loop() {
  long now = millis();
  setpoint.poll(now);
  thermometer.poll(now);
}


