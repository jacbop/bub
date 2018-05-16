// Basic operation of rotary encoder controlling OLED with Wifi

#include "Setpoint.h"
#include "Display.h"
#include "Wifi.h"

Wifi wifi;
Display display;

void onSetpoint(double setpoint) {
  display.setSetpoint(setpoint);
  display.setTemperature(setpoint);
}

void onValue(double value) {
  display.setValue(value);
}

Setpoint setpoint(D3, D4, D5, 10.0, 80.0, 22.0, 3000, onSetpoint, onValue);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder + OLED + Wifi Test:");
  setpoint.start(false);
  display.start(false);
  wifi.start(false);
}


void loop() {
  setpoint.poll();
}



