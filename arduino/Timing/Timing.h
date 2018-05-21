#ifndef HEADER_TIMING
#define HEADER_TIMING

#include "Arduino.h"

class Timing {
  private:
    
  public:
    Timing();
    long getInstant();
    long elapsedSince(long pastInstant);
    bool hasElapsed(long pastInstant, long duration);
};

#endif
