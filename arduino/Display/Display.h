#ifndef HEADER_DISPLAY
#define HEADER_DISPLAY

#include "Arduino.h"
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

// https://github.com/acrobotic/Ai_Ardulib_SSD1306

class Display {
  private:
  
  public:
    //
    Display();
    void start(bool debug);
    void setSetpoint(double value);
    void setValue(double value);
    void setTemperature(double value);
};

#endif
