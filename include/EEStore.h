#ifndef EEStore_h
#define EEStore_h

#include <Arduino.h>

#if defined(ARDUINO_ARCH_SAMD)
#include <SparkFun_External_EEPROM.h>
extern ExternalEEPROM EEPROM;
#else
#include <EEPROM.h>
#endif

#define EESTORE_ID "DCC++"

struct EEStoreData{
  char id[sizeof(EESTORE_ID)];
  int nTurnouts;
  int nSensors;  
  int nOutputs;
};

class EEStore {

  EEStoreData data;
  int         eeAddress;

  static void dump(int);

  void clear();

  void advance (int n) {
    eeAddress += n;
  }
  void reset() {
      eeAddress = sizeof(EEStore);
  }
  int pointer() {
      return eeAddress;
  }

  public:

    void load();
    void store();
};

#endif
