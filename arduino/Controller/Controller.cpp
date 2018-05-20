#include "Controller.h"

Controller::Controller(uint8_t coolPin, uint8_t heatPin, double differential, double defaultSetpoint, void (*onCool)(bool isCalling), void (*onHeat)(bool isCalling)):
  coolPin(coolPin), heatPin(heatPin), isCallingForCool(false), isCallingForHeat(false), differential(differential), setPoint(defaultSetpoint), onCool(onCool), onHeat(onHeat) {
  pinMode(coolPin, OUTPUT);
  pinMode(heatPin, OUTPUT);
}

void Controller::start(bool debug) {
  Serial.println("Device 0 Resolution: ");
}

void Controller::setSetpoint(double setPoint) {
  this->setPoint = setPoint;
}

bool Controller::shouldCool(double temperature) {
  return temperature > (setPoint + differential);
}

bool Controller::shouldHeat(double temperature) {
  return temperature < (setPoint - differential);
}

void Controller::setTemperature(double temperature) {
  Serial.println(temperature);
  Serial.println(" sp ");
  Serial.println(setPoint);
  Serial.println(" diff ");
  Serial.println(differential);
  if (shouldCool(temperature)) {
    if (!isCallingForCool) {
      isCallingForCool = true;
      onCool(true);
    }
    if (isCallingForHeat) {
      isCallingForHeat = false;
      onHeat(false);
    }
  } else if (shouldHeat(temperature)) {
    if (isCallingForCool) {
      isCallingForCool = false;
      onCool(false);
    }
    if (!isCallingForHeat) {
      isCallingForHeat = true;
      onHeat(true);
    }
  } else {
    if (isCallingForCool) {
      isCallingForCool = false;
      onCool(false);
    }
    if (isCallingForHeat) {
      isCallingForHeat = false;
      onHeat(false);
    }
  }
}


