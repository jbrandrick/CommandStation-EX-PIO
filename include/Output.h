#ifndef Output_h
#define Output_h

#include <Arduino.h>

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

    void populate (uint16_t, uint8_t, uint8_t, uint8_t = 0);
    void activate(int s);
    static void printAll(Print *);
};
  
#endif