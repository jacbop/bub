#include "Controller.h"

void onCool(bool isCalling) {
  Serial.print("cooling: ");
  Serial.print(isCalling);
}

void onHeat(bool isCalling) {
  Serial.print("heating: ");
  Serial.print(isCalling);
}

Controller controller(D0, D4, 2.0, onCool, onHeat);

void setup()
{
  Serial.begin(115200);
  Serial.println("Relay switching logic test:");
  controller.start(false);
}

void loop()
{
  long now = millis();
  double sp = (now / 100) % 100;
  double tmp = now % 100;
  Serial.print("setpoint: ");
  Serial.print(sp);
  Serial.print(" temp: ");
  Serial.println(tmp);
  controller.setSetpoint(sp);
  controller.setTemperature(tmp);
  delay(20000);
}
