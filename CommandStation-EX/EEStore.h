#ifndef EEStore_h
#define EEStore_h

#include <Arduino.h>
#include "StringFormatter.h"

#if defined(ARDUINO_ARCH_SAMD)
#include <SparkFun_External_EEPROM.h>
extern ExternalEEPROM EEPROM;
#else
#include <EEPROM.h>
#endif

#define EESTORE_ID "DCC++"

struct EEStoreData {
  char id[sizeof(EESTORE_ID)];
  int nTurnouts;
  int nSensors;  
  int nOutputs;
};

class EEStore {

  EEStoreData data;
  int         eeAddress;

  void loadTurnouts ();
  void loadSensors ();
  void loadOutputs ();

  void advancePointer (int offset) {
    eeAddress += offset;
  }
  void resetPointer () {
    eeAddress = sizeof(EEStoreData);
  }
  int pointer () {
    return eeAddress;
  }

  public:

    EEStore () {}

    void init ();
    void store ();
    void dump (int);

    void clearStoreData () {
      sprintf (data.id, EESTORE_ID);
      data.nTurnouts = 0;
      data.nSensors  = 0;
      data.nOutputs  = 0;
      EEPROM.put (0, data);
    }
    void send (Print* stream) {
      StringFormatter::send (stream, F("<e %d %d %d>\n"), data.nTurnouts, data.nSensors, data.nOutputs);
    }
};

#endif
