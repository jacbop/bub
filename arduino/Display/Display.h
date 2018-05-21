#ifndef HEADER_DISPLAY
#define HEADER_DISPLAY

#include "Arduino.h"
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

// https://github.com/acrobotic/Ai_Ardulib_SSD1306

class Display {
  private:
   double lastValue;
   double lastTemperature;
   bool lastCool;
   bool lastHeat;
   bool isWaitingForCompressor;
   String lastBanner;
   void refresh();
  
  public:
    //
    Display(double defaultValue);
    void start(bool debug);
    void setSetpoint(double value);
    void setValue(double value);
    void setTemperature(double value);
    void setWaitingForCompressor(bool isWaiting);
    void setCool(bool isCalling);
    void setHeat(bool isCalling);
    void setBanner(String banner);
};

#endif
