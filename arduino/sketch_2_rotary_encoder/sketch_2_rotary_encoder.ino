// Basic operation of rotary encoder


#include "Setpoint.h"

void onSetpoint(double setpoint) {
  Serial.print("Setpoint: ");
  Serial.println(setpoint);
}

void onValue(double value) {
  Serial.print("Value: ");
  Serial.println(value);
}

Setpoint setpoint(D5, D6, D7, 10.0, 80.0, 22.0, 3000, onSetpoint, onValue);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
  setpoint.start(false);
}


void loop() {
  long now = millis();
  setpoint.poll(now);
}


