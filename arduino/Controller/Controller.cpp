#include "Controller.h"
#include "Timing.h"

Timing timing;

Controller::Controller(uint8_t coolPin, uint8_t heatPin, double differential, long compressorDelayTime, double defaultSetpoint, void (*onCool)(bool isCalling), void (*onHeat)(bool isCalling), void (*onWaitingForCompressor)()):
  coolPin(coolPin), heatPin(heatPin), isCallingForCool(false), isCallingForHeat(false), isWaitingForCompressor(false), differential(differential), compressorDelayTime(compressorDelayTime), lastCompressorOffTime(0), setPoint(defaultSetpoint), onCool(onCool), onHeat(onHeat), onWaitingForCompressor(onWaitingForCompressor) {
  pinMode(coolPin, OUTPUT);
  pinMode(heatPin, OUTPUT);
  lastCompressorOffTime = timing.getInstant();
}

void Controller::start(bool debug) {
  Serial.println("Controller logic starting.");
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
    if (!isWaitingForCompressor) {
      Serial.println("waiting for compressor");
      onWaitingForCompressor();
      isWaitingForCompressor = true;
    }
    if (timing.hasElapsed(lastCompressorOffTime, compressorDelayTime)) {
      Serial.println("compressor is ready");
      Serial.println("cool on");
      isCallingForCool = true;
      digitalWrite(coolPin, HIGH);
      onCool(true);
      isWaitingForCompressor = false;
    }
  }
  if (pin == heatPin) {
    if (!isCallingForHeat) {
      Serial.println("heat on");
      isCallingForHeat = true;
      digitalWrite(heatPin, HIGH);
      onHeat(true);
    }
  }
}

bool Controller::relayOff(uint8_t pin) {
  if (pin == coolPin) {
    if (isCallingForCool) {
      Serial.println("cool off");
      isCallingForCool = false;
      digitalWrite(coolPin, LOW);
      onCool(false);
      lastCompressorOffTime = timing.getInstant();
    }
  }
  if (pin == heatPin) {
    if (isCallingForHeat) {
      Serial.println("heat off");
      isCallingForHeat = false;
      digitalWrite(heatPin, LOW);
      onHeat(false);
    }
  }
}

void Controller::setTemperature(double temperature) {
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


