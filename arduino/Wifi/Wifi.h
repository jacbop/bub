#ifndef HEADER_WIFI
#define HEADER_WIFI

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "credentials.h"

class Wifi {
  private:
    IPAddress ip;
    char* ssid;
    char* password;
    void (*onIpAddress)(String ipAddress);

  public:
    //
    Wifi(char* ssid, char* password, void (*onIpAddress)(String ipAddress));
    void start(bool debug);
};

#endif
