#include "Wifi.h"
#include "credentials.h"

Wifi::Wifi() {
  ip[0] = 0;
  ip[1] = 0;
  ip[2] = 0;
  ip[3] = 0;
}

void Wifi::start(bool debug) {
  char* ssid = WIFI_SSID;
  char* password = WIFI_PASSWD;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  ip = WiFi.localIP();
}
