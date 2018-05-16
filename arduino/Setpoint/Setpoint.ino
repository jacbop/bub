#include "Setpoint.h"

void onSetpoint(double setpoint) {
  Serial.print("Setpoint: ");
  Serial.print(setpoint);
  Serial.println("C");
}

void onValue(double value) {
  Serial.print("Value: ");
  Serial.print(value);
  Serial.println("C");
}

Setpoint setpoint(D1, D2, D3, -10.0, 120.0, 20.0, 3000, onSetpoint, onValue);

void setup() {
  Serial.begin(115200);
  Serial.println("Setpoint Test:");
  setpoint.start(true);
}


void loop() {
  setpoint.poll();
}


