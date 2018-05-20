#include "Controller.h"

Controller::Controller(uint8_t coolPin, uint8_t heatPin, double differential, void (*onCool)(bool isCalling), void (*onHeat)(bool isCalling)):
  coolPin(coolPin), heatPin(heatPin), isCallingForCool(false), isCallingForHeat(false), setPoint(-1000.0), differential(differential), onCool(onCool), onHeat(onHeat) {
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
  // time limit and other params
  return (setPoint > -1000.0) && (temperature > setPoint + differential);
}

bool Controller::shouldHeat(double temperature) {
  return (setPoint > -1000.0) && (temperature < setPoint - differential);
}

void Controller::setTemperature(double temperature) {
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


