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
    bool isWaitingForCompressor;
    double setPoint;
    double differential;
    long compressorDelayTime;
    long lastCompressorOffTime;
    void (*onCool)(bool isCalling);
    void (*onHeat)(bool isCalling);
    void (*onWaitingForCompressor)(bool isWaiting);
    bool shouldCool(double temperature);
    bool shouldHeat(double temperature);
    bool relayOn(uint8_t pin);
    bool relayOff(uint8_t pin);

  public:
    Controller(uint8_t coolPin, uint8_t heatPin, double differential, long compressorDelayTime, double defaultSetpoint, void (*onCool)(bool isCalling), void (*onHeat)(bool isCalling), void (*onWaitingForCompressor)(bool isWaiting));
    void start(bool debug);
    void setSetpoint(double setPoint);
    void setTemperature(double temperature);
};

#endif
