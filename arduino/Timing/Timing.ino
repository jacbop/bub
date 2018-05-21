#include "Timing.h"
// https://arduino.stackexchange.com/questions/12587/how-can-i-handle-the-millis-rollover

Timing timing;
uint instantJustBeforeRollover = 4294967200;
uint durationLongEnoughForATest = 30000;

void setup()
{
  Serial.begin(115200);
  Serial.println("Timing test:");

}

void loop()
{
        Serial.println(millis());
  delay(1000);
  if (timing.hasElapsed(instantJustBeforeRollover, durationLongEnoughForATest)) {
      Serial.println("Elapsed!");
  } else {
      Serial.println("not elapsed yet");
  }
}

