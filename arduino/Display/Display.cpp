#include "Display.h"

Display::Display() {
}

void Display::start(bool debug) {
  Wire.begin();
  oled.init();
  oled.clearDisplay();
}

void Display::setSetpoint(double value) {
 oled.clearDisplay();
 setValue(value);
}


void Display::setValue(double value) {
  String text = String(value, 2);
  oled.setTextXY(0, 0);
  oled.putString("SP   = ");
  oled.putString(text);
  oled.putString("C");
}

void Display::setTemperature(double value) {
  String text = String(value, 2);
  oled.setTextXY(2, 0);
  oled.putString("Temp = ");
  oled.putString(text);
  oled.putString("C");
}


//   total of 8x16
//
//    void setTextXY(unsigned char Row, unsigned char Column);
//    void clearDisplay();
//    void setBrightness(unsigned char Brightness);
//    bool putChar(unsigned char c);
//    void putString(const char *string);
//    void putString(String string);
//    unsigned char putNumber(long n);
//    unsigned char putFloat(float floatNumber,unsigned char decimal);
//    unsigned char putFloat(float floatNumber);
