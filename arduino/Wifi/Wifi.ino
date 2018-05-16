#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "credentials.h"

ESP8266WebServer server;
char* ssid = WIFI_SSID;
char* password = WIFI_PASSWD;
uint8_t pin_relay = 16;

void setup() {
  pinMode(pin_relay, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/grind", HTTP_POST, grind);
  server.begin();
}

void loop() {
  server.handleClient();
}

void grind() {
  unsigned long millis = 0;
  if (server.args() != 0) {
    millis = server.arg(0).toInt();
  }
  if (millis <= 0) {
    millis = 20000;
  }
  digitalWrite(pin_relay, true);
  Serial.println(WiFi.localIP());
  server.send(200, "OK");
  delay(millis);
  digitalWrite(pin_relay, false);
}

