#ifndef HEADER_ROTARYENCODER
#define HEADER_ROTARYENCODER

#include <Encoder.h>


  // https://github.com/PaulStoffregen/Encoder
  // open serial monitor and you can observe value increasing clockwise,
  // descreasing counter clockwise and resetting to zero on button push

  class RotaryEncoder {
    private:
      Encoder _encoder;
      long _minTicks;
      long _maxTicks;
      long _commitDelay;
      long _currTicks;
      long _prevTicks;
      bool _isButtonPressed;
      long _buttonDebounceStartTime;
      bool _needToCommit;
      long _commitDebounceStartTime;
      void (*_onNewValue)(long newValue);

      long checkBounds(long tickObservation);
      void handleCommit();

      static RotaryEncoder* _instance;
      static void handleKey();
      
    public:
      // 
      RotaryEncoder(long minTicks, long maxTicks, long startTicks, long commitDelay, void (*onNewValue)(long newValue)); 
      void start(void);
      void poll(void);
  };
   
#endif
