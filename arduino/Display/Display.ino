#include "Display.h"

Display display(20.0);

void setup()
{
  display.start(false);
}

int edge = 0;
void loop()
{
  if (edge == 0 && millis() % 10000 < 10) {
    edge = 1;
    display.setValue(random(10,30));
    display.setTemperature(random(10,30));
  }
  if (edge == 1 && millis() % 10000 > 9990) {
    display.setSetpoint(random(10,30));
    display.setTemperature(random(10,30));
    edge = 0;
  }
}
