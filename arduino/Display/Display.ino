#include "Display.h"

Display display;

void setup()
{
  display.start(false);
}

int edge = 0;
void loop()
{
  if (edge == 0 && millis() % 1000 < 10) {
    edge = 1;
    display.setValue(millis() % 100);
    display.setTemperature(millis() % 100);
  }
  if (edge == 1 && millis() % 1000 > 990) {
    display.setSetpoint(millis() % 100);
    display.setTemperature(millis() % 100);
    edge = 0;
  }
}
