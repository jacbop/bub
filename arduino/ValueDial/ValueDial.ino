#include "ValueDial.h"

void onNewValue(long newValue) {
  Serial.print("New Value: ");
  Serial.println(newValue);
}

ValueDial valueDial(D1, D2, D3, 0, 1000, 200, 3000, onNewValue);

void setup() {
  Serial.begin(115200);
  Serial.println("ValueDial Test:");
  valueDial.start();
}


void loop() {
  valueDial.poll();
}


