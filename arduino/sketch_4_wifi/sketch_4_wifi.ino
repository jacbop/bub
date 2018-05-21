// Basic operation of rotary encoder controlling OLED with Wifi

#include "Setpoint.h"
#include "Display.h"
#include "Wifi.h"

Display display(22.0);

void onIpAddress(String ipAddress) {
  display.setBanner(ipAddress);  
}

Wifi wifi(WIFI_SSID, WIFI_PASSWD, onIpAddress);

void onSetpoint(double setpoint) {
  display.setSetpoint(setpoint);
  display.setTemperature(setpoint);
}

void onValue(double value) {
  display.setValue(value);
}

Setpoint setpoint(D5, D6, D7, 10.0, 80.0, 22.0, 3000, onSetpoint, onValue);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder + OLED + Wifi Test:");
  setpoint.start(false);
  display.start(false);
  wifi.start(false);
}


void loop() {
  long now = millis();
  setpoint.poll(now);
}



