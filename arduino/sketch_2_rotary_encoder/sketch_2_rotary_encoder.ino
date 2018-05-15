// Basic operation of rotary encoder


#include "RotaryEncoder.h"

void onNewValue(long newValue) {
  Serial.print("New Value: ");
  Serial.println(newValue);
}

RotaryEncoder rotaryEncoder(D1, D2, D3, 0, 1000, 200, 3000, onNewValue);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
  rotaryEncoder.start();
}


void loop() {
  rotaryEncoder.poll();
}


