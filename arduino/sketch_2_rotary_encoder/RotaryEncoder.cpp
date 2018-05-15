#include "RotaryEncoder.h"
#include "Arduino.h"

RotaryEncoder* RotaryEncoder::instance = NULL;

RotaryEncoder::RotaryEncoder(
  uint8_t clkPin,
  uint8_t dtPin,
  uint8_t swPin,
  long minTicks,
  long maxTicks,
  long startTicks,
  long commitDelay,
  void (*onNewValue)(long newValue)):
  encoder(clkPin, dtPin),
  minTicks(minTicks),
  maxTicks(maxTicks),
  commitDelay(commitDelay),
  currTicks(startTicks),
  prevTicks(startTicks),
  isButtonPressed(false),
  buttonDebounceStartTime(0),
  needToCommit(false),
  commitDebounceStartTime(0),
  onNewValue(onNewValue)
{
  pinMode(swPin, INPUT_PULLUP);
  attachInterrupt(swPin, RotaryEncoder::handleKey, RISING);
  instance = this;
}

void RotaryEncoder::start(void) {
  encoder.write(currTicks);
}

void RotaryEncoder::handleCommit() {
  needToCommit = false;
  commitDebounceStartTime = millis();
  Serial.print("COMMIT: ");
  Serial.println(currTicks);
  onNewValue(currTicks);
}

void RotaryEncoder::handleKey() {
  instance->isButtonPressed = true;
  Serial.println("PRESS.");
  instance->handleCommit();
}

long RotaryEncoder::checkBounds(long tickObservation) {
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

void RotaryEncoder::poll(void) {
  currTicks = checkBounds(encoder.read());
  if (currTicks != prevTicks) {
    prevTicks = currTicks;
    commitDebounceStartTime = millis();
    needToCommit = true;
    Serial.print("==> ");
    Serial.println(currTicks);
  }
  if (needToCommit && ((millis() - commitDebounceStartTime) > 3000)) {
    handleCommit();
    needToCommit = false;
    commitDebounceStartTime = millis();
  }
  if (isButtonPressed && ((millis() - buttonDebounceStartTime) > 150)) {
    isButtonPressed = false;
    buttonDebounceStartTime = millis();
  }
}
