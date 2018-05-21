#include "Display.h"

Display::Display(double defaultValue): lastValue(defaultValue), lastTemperature(defaultValue), lastCool(false), lastHeat(false), lastBanner("  Wilberding   ") {
}

void Display::start(bool debug) {
  Wire.begin();
  oled.init();
  oled.clearDisplay();
  refresh();
}

void Display::refresh() {
  oled.setTextXY(0, 0);
  oled.putString(lastBanner);

  String valueText = String(lastValue, 2);
  oled.setTextXY(2, 0);
  oled.putString("SP   = ");
  oled.putString(valueText);
  oled.putString("C");

  String tempText = String(lastTemperature, 2);
  oled.setTextXY(4, 0);
  oled.putString("Temp = ");
  oled.putString(tempText);
  oled.putString("C");

  String coolText = (lastCool) ? String(" (*)") : String("    ");
  oled.setTextXY(6, 0);
  oled.putString("Cool = ");
  oled.putString(coolText);

  String heatText = (lastHeat) ? String(" (*)") : String("    ");
  oled.setTextXY(7, 0);
  oled.putString("Heat = ");
  oled.putString(heatText);
}

void Display::setSetpoint(double value) {
  oled.clearDisplay();
  refresh();
}

void Display::setValue(double value) {
  lastValue = value;
  refresh();
}

void Display::setTemperature(double value) {
  lastTemperature = value;
  refresh();
}

void Display::setCool(bool isCalling) {
  lastCool = isCalling;
  refresh();
}

void Display::setHeat(bool isCalling) {
  lastHeat = isCalling;
  refresh();
}

void Display::setBanner(String banner) {
  lastBanner = banner;
  refresh();
}
