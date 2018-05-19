#ifndef HEADER_SETPOINT
#define HEADER_SETPOINT

#include "Arduino.h"
#include <Encoder.h>

// https://github.com/PaulStoffregen/Encoder
// open serial monitor and you can observe value increasing clockwise,
// descreasing counter clockwise and resetting to zero on button push

class Setpoint {
  private:
    Encoder encoder;
    long minTicks;
    long maxTicks;
    long commitDelay;
    long minValue;
    long currTicks;
    long prevTicks;
    bool isButtonPressed;
    long buttonDebounceStartTime;
    bool needToCommit;
    long commitDebounceStartTime;
    void (*onSetpoint)(double setpoint);
    void (*onValue)(double value);

    long checkBounds(long tickObservation);
    void handleCommit();

    static bool debug;
    static Setpoint* instance;
    static void handleKey();

  public:
    //
    Setpoint(
      uint8_t clkPin,
      uint8_t dtPin,
      uint8_t swPin,
      double minValue,
      double maxValue,
      double startValue,
      long commitDelay,
      void (*onSetpoint)(double setpoint),
      void (*onValue)(double value)
    );
    void start(bool debug);
    void poll(long millis);
};

#endif
