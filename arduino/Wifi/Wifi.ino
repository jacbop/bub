#include "Wifi.h"

void onIpAddress(String ipAddress) {
  Serial.println(ipAddress);
}

Wifi wifi(WIFI_SSID, WIFI_PASSWD, onIpAddress);

void setup() {
  Serial.begin(115200);
  Serial.println("Wifi connection test:");
  wifi.start(false);
}

void loop() {
}

