#ifndef HEADER_ROTARYENCODER
#define HEADER_ROTARYENCODER

#include "Arduino.h"
#include <Encoder.h>

// https://github.com/PaulStoffregen/Encoder
// open serial monitor and you can observe value increasing clockwise,
// descreasing counter clockwise and resetting to zero on button push

class RotaryEncoder {
  private:
    Encoder encoder;
    long minTicks;
    long maxTicks;
    long commitDelay;
    long currTicks;
    long prevTicks;
    bool isButtonPressed;
    long buttonDebounceStartTime;
    bool needToCommit;
    long commitDebounceStartTime;
    void (*onNewValue)(long newValue);

    long checkBounds(long tickObservation);
    void handleCommit();

    static RotaryEncoder* instance;
    static void handleKey();

  public:
    //
    RotaryEncoder(
      uint8_t clkPin,
      uint8_t dtPin,
      uint8_t swPin,
      long minTicks,
      long maxTicks,
      long startTicks,
      long commitDelay,
      void (*onNewValue)(long newValue)
    );
    void start(void);
    void poll(void);
};

#endif