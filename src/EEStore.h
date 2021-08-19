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

struct EEStoreData {
  char id[sizeof(EESTORE_ID)];
  int nTurnouts;
  int nSensors;  
  int nOutputs;
};

class EEStore {

  EEStoreData data;
  int         eeAddress;

  void loadTurnouts (EEStoreData*);
  void loadSensors (EEStoreData*);
  void loadOutputs (EEStoreData*);

  static void dump(int);

  void clearStoreData () {
    sprintf (data.id, EESTORE_ID);
    data.nTurnouts = 0;
    data.nSensors  = 0;
    data.nOutputs  = 0;
    EEPROM.put (0, data);
  }
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

    void load();
    void store();
};

#endif
