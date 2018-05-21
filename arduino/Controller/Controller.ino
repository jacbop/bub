#include "Controller.h"

void onCool(bool isCalling) {
  Serial.print("cooling: ");
  Serial.println(isCalling);
}

void onHeat(bool isCalling) {
  Serial.print("heating: ");
  Serial.println(isCalling);
}

void onWaitingForCompressor(bool isWaiting) {
  Serial.print("waiting for compressor: ");
  Serial.println(isWaiting);
}

Controller controller(D0, D4, 2.0, 120000, 20.0, onCool, onHeat, onWaitingForCompressor);

void setup()
{
  Serial.begin(115200);
  Serial.println("Relay switching logic test:");
  controller.start(false);
}

void loop()
{
  double sp = random(10, 30);
  double tmp = random(10, 30);
  Serial.print("setpoint: ");
  Serial.print(sp);
  Serial.print(" temp: ");
  Serial.println(tmp);
  controller.setSetpoint(sp);
  controller.setTemperature(tmp);
  delay(8000);
}
