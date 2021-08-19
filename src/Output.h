#ifndef Output_h
#define Output_h

#include <Arduino.h>
#include <EEPROM.h>
#include "StringFormatter.h"

struct OutputData {
  uint8_t   oStatus;
  uint16_t  id;
  uint8_t   pin; 
  uint8_t   iFlag; 
};

struct BrokenOutputData {
  uint8_t   oStatus;
  uint8_t   id;
  uint8_t   pin;
  uint8_t   iFlag;
};

class Output {
  private:
    int num;  // EEPROM pointer (Chris has no idea what this is all about!)

  public:
    struct OutputData data;

    void populate ( OutputData );
    void populate (uint16_t, uint8_t, uint8_t, uint8_t = 0);
    void activate (int s);

    uint8_t activeValue () {
      // set state of output pin to HIGH or LOW
      // depending on whether bit zero of iFlag is set to 0 (ACTIVE=HIGH) or 1 (ACTIVE=LOW)
      return data.oStatus ^ bitRead (data.iFlag, 0);
    }
    void persistStatus () {
      if (num > 0)
        EEPROM.put (num, data.oStatus);
    }
    void send ( Print *stream ) {
      StringFormatter::send (stream, F("<Y %d %d>\n"), data.id, data.oStatus);
    }
};
  
#endif