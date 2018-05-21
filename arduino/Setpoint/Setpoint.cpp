#include "Setpoint.h"

#define TICK_RESOLUTION 4.0

Setpoint* Setpoint::instance = NULL;
bool Setpoint::debug = false;

Setpoint::Setpoint(
  uint8_t clkPin,
  uint8_t dtPin,
  uint8_t swPin,
  double minValue,
  double maxValue,
  double startValue,
  long commitDelay,
  void (*onSetpoint)(double setpoint),
  void (*onValue)(double value)):
  encoder(clkPin, dtPin),
  minValue(minValue),
  minTicks(0),
  maxTicks((maxValue - minValue) * TICK_RESOLUTION),
  commitDelay(commitDelay),
  currTicks((startValue - minValue) * TICK_RESOLUTION),
  prevTicks((startValue - minValue) * TICK_RESOLUTION),
  isButtonPressed(false),
  buttonDebounceStartTime(0),
  needToCommit(false),
  commitDebounceStartTime(0),
  timing(),
  onSetpoint(onSetpoint),
  onValue(onValue)
{
  pinMode(swPin, INPUT_PULLUP);
  attachInterrupt(swPin, Setpoint::handleKey, RISING);
  instance = this;
}

void Setpoint::start(bool debug) {
  this->debug = debug;
  encoder.write(currTicks);
  onValue((currTicks / TICK_RESOLUTION) + minValue);
  onSetpoint((currTicks / TICK_RESOLUTION) + minValue);
}

void Setpoint::handleCommit() {
  needToCommit = false;
  commitDebounceStartTime = timing.getInstant();
  if (debug) {
    Serial.print("COMMIT: ");
    Serial.print(currTicks);
    Serial.print(" ");
    Serial.println((currTicks / TICK_RESOLUTION) + minValue);
  }
  onSetpoint((currTicks / TICK_RESOLUTION) + minValue);
}

void Setpoint::handleKey() {
  instance->isButtonPressed = true;
  if (debug) {
    Serial.println("PRESS.");
  }
  instance->handleCommit();
}

long Setpoint::checkBounds(long tickObservation) {
  if (tickObservation < minTicks) {
    encoder.write(minTicks);
    return minTicks;
  }
  if (tickObservation > maxTicks) {
    encoder.write(maxTicks);
    return maxTicks;
  }
  return tickObservation;
}

void Setpoint::poll(long recentInstant) {
  currTicks = checkBounds(encoder.read());
  if (currTicks != prevTicks) {
    prevTicks = currTicks;
    commitDebounceStartTime = recentInstant;
    needToCommit = true;
    if (debug) {
      Serial.print("==> ");
      Serial.print(currTicks);
      Serial.print(" ");
      Serial.println((currTicks / TICK_RESOLUTION) + minValue);
    }
    onValue((currTicks / TICK_RESOLUTION) + minValue);
  }
  if (needToCommit && timing.hadElapsed(commitDebounceStartTime, recentInstant, commitDelay)) {
    handleCommit();
    needToCommit = false;
    commitDebounceStartTime = recentInstant;
  }
  if (isButtonPressed && timing.hadElapsed(buttonDebounceStartTime, recentInstant, 150)) {
    isButtonPressed = false;
    buttonDebounceStartTime = recentInstant;
  }
}
