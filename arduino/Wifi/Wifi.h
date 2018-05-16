#ifndef HEADER_WIFI
#define HEADER_WIFI

#include "Arduino.h"
#include <ESP8266WiFi.h>


class Wifi {
  private:
    IPAddress ip;
  
  public:
    //
    Wifi();
    void start(bool debug);
};

#endif
