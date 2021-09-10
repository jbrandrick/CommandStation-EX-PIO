#ifndef Loco_h
#define Loco_h

#include <Arduino.h>
#include "StringFormatter.h"

class Throttle {

  private:

    int           cab;
    byte          speedCode;
    byte          groupFlags;
    unsigned long functions;

    void updateGroupflags (int16_t);

  public:

    int     getFn (int16_t);
    void    setFn (int16_t, bool);
    int     changeFn (int16_t, bool);

    // these getters are temporary for current state of DCC::issueReminder
    int getCab () {
      return cab;
    }
    byte getSpeedCode () {
      return speedCode;
    }
    byte getGroupFlags () {
      return groupFlags;
    }
    unsigned long getFunctions () {
      return functions;
    }

    void forgetLoco () {   
      cab = 0;
    }
    uint8_t getThrottleSpeed () {
      return speedCode & 0x7F;
    }
    void setThrottleSpeed (byte speedCodeIn) {
      speedCode = (speedCode & 0x80) |  (speedCodeIn & 0x7f);
    }
    bool getThrottleDirection () {
      return (speedCode & 0x80) != 0;
    }
    void updateLocoReminder (byte speedCodeIn) {   
      speedCode = speedCodeIn;
    }
    void displayCab (Print* stream) {
      StringFormatter::send (stream, F("cab=%d, speed=%d, dir=%c \n"),       
          cab, getThrottleSpeed (), getThrottleDirection () ? 'F' : 'R');
    }

};

#endif