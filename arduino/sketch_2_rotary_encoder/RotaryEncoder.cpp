#include "RotaryEncoder.h"
#include "Arduino.h"

RotaryEncoder* RotaryEncoder::_instance = NULL;

RotaryEncoder::RotaryEncoder(long minTicks, long maxTicks, long startTicks, long commitDelay, void (*onNewValue)(long newValue)): _encoder(D1, D2) {
  _minTicks = minTicks;
  _maxTicks = maxTicks;
  _commitDelay = commitDelay;
  _currTicks = startTicks;
  _prevTicks =- startTicks;
  _isButtonPressed = false;
  _buttonDebounceStartTime = 0;
  _needToCommit = false;
  _commitDebounceStartTime = 0;
  _instance = this;
  _onNewValue = onNewValue;
}

void RotaryEncoder::start(void) {
   pinMode(D3, INPUT_PULLUP);
   attachInterrupt(D3, RotaryEncoder::handleKey, RISING);
   _encoder.write(_currTicks);
}

void RotaryEncoder::handleCommit() {
    _needToCommit = false;
    _commitDebounceStartTime = millis();
    Serial.print("COMMIT: ");
    Serial.println(_currTicks);
    _onNewValue(_currTicks);
}

void RotaryEncoder::handleKey() {
  _instance->_isButtonPressed = true;
  Serial.println("PRESS.");
  _instance->handleCommit();
}

long RotaryEncoder::checkBounds(long tickObservation) {
  if (tickObservation < _minTicks) {
    _encoder.write(_minTicks);
    return _minTicks;
  }
  if (tickObservation > _maxTicks) {
    _encoder.write(_maxTicks);
    return _maxTicks;
  }
  return tickObservation;
}

void RotaryEncoder::poll(void){
  _currTicks = checkBounds(_encoder.read());
  if (_currTicks != _prevTicks) {
    _prevTicks = _currTicks;
    _commitDebounceStartTime = millis();
    _needToCommit = true;
    Serial.print("==> ");
    Serial.println(_currTicks);
  }
  if (_needToCommit && ((millis() - _commitDebounceStartTime) > 3000)) {
    handleCommit();
    _needToCommit = false;
    _commitDebounceStartTime = millis();
  }
  if (_isButtonPressed && ((millis() - _buttonDebounceStartTime) > 150)) {
    _isButtonPressed = false;
    _buttonDebounceStartTime = millis();
  }
}
