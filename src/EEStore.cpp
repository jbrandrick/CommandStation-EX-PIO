/*
 *  © 2013-2016 Gregg E. Berman
 *  © 2020, Chris Harlow. All rights reserved.
 *  © 2020, Harald Barth.
 *
 *  This file is part of Asbelos DCC API
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
#include "EEStore.h"
#include "Turnout.h"
#include "Sensor.h"
#include "Output.h"
#include "DIAG.h"
#include "DccManager.h"


#if defined(ARDUINO_ARCH_SAMD)
  ExternalEEPROM EEPROM;
#endif

void EEStore::load() {

#if defined(ARDUINO_ARCH_SAMD)
  EEPROM.begin(0x50);     // Address for Microchip 24-series EEPROM with all three A pins grounded (0b1010000 = 0x50)
#endif

  EEStoreData* eeStoreData = (EEStoreData *) calloc (1, sizeof(EEStoreData));
  EEPROM.get (0, eeStoreData);

  // check to see that eeStore contains valid DCC++ ID
  // if not, create blank eeStore structure (no turnouts, no sensors) and save it back to EEPROM
  if (strncmp (eeStoreData->id, EESTORE_ID, sizeof(EESTORE_ID)) != 0)
    clearStoreData ();

  resetPointer ();

  loadTurnouts (eeStoreData);
  loadSensors (eeStoreData);
  loadOutputs (eeStoreData);

  free (eeStoreData);
}


void EEStore::loadTurnouts (EEStoreData* eeStoreData) {
  Turnout* turnout;
  TurnoutData turnoutData;

  for ( int i = 0; i < eeStoreData->nTurnouts; i++ ) {
    EEPROM.get ( eeAddress, turnoutData );
    turnout = DCC_MANAGER->turnouts->getOrAdd (turnoutData.id);
    turnout->populate (turnoutData);
    turnout->setTurnoutDataOffset (eeAddress);
    advancePointer (sizeof(turnoutData));
  }
}

void EEStore::loadSensors (EEStoreData* eeStoreData) {
  Sensor* sensor;
  SensorData sensorData;

  for ( int i = 0; i < eeStoreData->nSensors; i++ ) {
    EEPROM.get (eeAddress, sensorData);
    sensor = DCC_MANAGER->sensors->getOrAdd (sensorData.snum);
    sensor->populate (sensorData);
    advancePointer (sizeof(sensorData));
  }
}

void EEStore::loadOutputs (EEStoreData* eeStoreData) {
  Output* output;
  OutputData outputData;

  for ( int i = 0; i < eeStoreData->nOutputs; i++ ) {
    EEPROM.get (eeAddress, outputData);
    output = DCC_MANAGER->outputs->getOrAdd (outputData.id);
    output->populate (outputData);
    advancePointer (sizeof(outputData));
  }
}


void EEStore::store (){
    resetPointer ();

    data.nTurnouts = 0;
    for ( HashList<Turnout>::Iterator iTurnout (DCC_MANAGER->turnouts->begin ()); iTurnout.hasNext (); iTurnout.next ()) {
      EEPROM.put ( pointer (), (*iTurnout)->data );
      advancePointer ( sizeof(TurnoutData) );
    }
    data.nTurnouts = DCC_MANAGER->turnouts->size ();

    data.nSensors = 0;
    for ( HashList<Sensor>::Iterator iSensor (DCC_MANAGER->sensors->begin ()); iSensor.hasNext (); iSensor.next ()) {
      EEPROM.put ( pointer (), (*iSensor)->data );
      advancePointer ( sizeof(SensorData) );
    }
    data.nSensors = DCC_MANAGER->sensors->size ();

    data.nOutputs = 0;
    for ( HashList<Output>::Iterator iOutput (DCC_MANAGER->outputs->begin ()); iOutput.hasNext (); iOutput.next ()) {
      EEPROM.put ( pointer (), (*iOutput)->data );
      advancePointer ( sizeof(OutputData) );
    }
    data.nOutputs = DCC_MANAGER->outputs->size ();

    EEPROM.put (0, data);
}

void EEStore::dump(int num) {
  byte b;
  DIAG(F("Addr  0x  char"));
  for (int n=0 ; n<num; n++) {
	EEPROM.get(n, b);
	DIAG(F("%d     %x    %c"),n,b,isprint(b) ? b : ' ');
  }
}
