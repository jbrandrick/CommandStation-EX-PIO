/*
 *  (c) 2020 Chris Harlow. All rights reserved.
 *  (c) 2020 Harald Barth. All rights reserved.
 *  
 *  This file is part of CommandStation-EX
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CommandStation.  If not, see <https://www.gnu.org/licenses/>.
 */
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
