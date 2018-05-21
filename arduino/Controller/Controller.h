#ifndef HEADER_CONTROLLER
#define HEADER_CONTROLLER

#include "Arduino.h"

// 

class Controller {
  private:
    uint8_t coolPin;
    uint8_t heatPin;
    bool isCallingForCool;
    bool isCallingForHeat;
    double setPoint;
    double differential;
    void (*onCool)(bool isCalling);
    void (*onHeat)(bool isCalling);
    bool shouldCool(double temperature);
    bool shouldHeat(double temperature);
    bool relayOn(uint8_t pin);
    bool relayOff(uint8_t pin);

  public:
    Controller(uint8_t coolPin, uint8_t heatPin, double differential, double defaultSetpoint, void (*onCool)(bool isCalling), void (*onHeat)(bool isCalling));
    void start(bool debug);
    void setSetpoint(double setPoint);
    void setTemperature(double temperature);
};

#endif
