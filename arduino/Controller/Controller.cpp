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

bool Controller::relayOn(uint8_t pin) {
  if (pin == coolPin) {
    if (!isCallingForCool) {
      isCallingForCool = true;
      digitalWrite(coolPin, HIGH);
      onCool(true);
    }
  }
  if (pin == heatPin) {
    if (!isCallingForHeat) {
      isCallingForHeat = true;
      digitalWrite(heatPin, HIGH);
      onHeat(true);
    }
  }
}

bool Controller::relayOff(uint8_t pin) {
  if (pin == coolPin) {
    if (isCallingForCool) {
      isCallingForCool = false;
      digitalWrite(coolPin, LOW);
      onCool(false);
    }
  }
  if (pin == heatPin) {
    if (isCallingForHeat) {
      isCallingForHeat = false;
      digitalWrite(heatPin, LOW);
      onHeat(false);
    }
  }
}

void Controller::setTemperature(double temperature) {
  Serial.println(temperature);
  Serial.println(" sp ");
  Serial.println(setPoint);
  Serial.println(" diff ");
  Serial.println(differential);
  if (shouldCool(temperature)) {
    relayOn(coolPin);
    relayOff(heatPin);
  } else if (shouldHeat(temperature)) {
    relayOff(coolPin);
    relayOn(heatPin);
  } else {
    relayOff(coolPin);
    relayOff(heatPin);
  }
}


