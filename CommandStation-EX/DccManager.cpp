#include "DccManager.h"

DccManager* DccManager::instance = nullptr;

 DccManager* DccManager::getInstance () {
  if (instance == nullptr)
    instance = new DccManager ();

  return instance;
}

void DccManager::init () {
  eeStore = new EEStore;

  turnouts = new HashList<Turnout>;
  sensors = new HashList<Sensor>;
  outputs = new HashList<Output>;
}


void DccManager::printAllTurnouts (Print* stream) {
  for ( HashList<Turnout>::Iterator iTurnout (turnouts->begin ()); iTurnout.hasNext (); iTurnout.next ()) {
    (*iTurnout)->send (stream);
  }
}

void DccManager::sendDefTurnouts (Print* stream) {
  for ( HashList<Turnout>::Iterator iTurnout (turnouts->begin ()); iTurnout.hasNext (); iTurnout.next ()) {
    (*iTurnout)->sendDef (stream);
  }
}

void DccManager::sendWifiTurnouts (RingStream* stream) {
  for ( HashList<Turnout>::Iterator iTurnout (turnouts->begin ()); iTurnout.hasNext (); iTurnout.next ()) {
    (*iTurnout)->sendWifi (stream);
  }
}


void DccManager::checkSensor (Stream& stream) {
  if (sensors->size () > 0) {
    if (!iSensor.hasNext ())
      iSensor.reset ();

    (*iSensor)->check (&stream);

    iSensor.next ();
  }
}

void DccManager::printAllSensors (Print* stream) {
  for ( HashList<Sensor>::Iterator iSensor (sensors->begin ()); iSensor.hasNext (); iSensor.next ()) {
    (*iSensor)->send (stream);
  }
}

void DccManager::sendDefSensors (Print* stream) {
  for ( HashList<Sensor>::Iterator iSensor (sensors->begin ()); iSensor.hasNext (); iSensor.next ()) {
    (*iSensor)->sendDef (stream);
  }
}


void DccManager::printAllOutputs (Print* stream) {
  for ( HashList<Output>::Iterator iOutput (outputs->begin ()); iOutput.hasNext (); iOutput.next ()) {
    (*iOutput)->send (stream);
  }
}

void DccManager::sendDefOutputs (Print* stream) {
  for ( HashList<Output>::Iterator iOutput (outputs->begin ()); iOutput.hasNext (); iOutput.next ()) {
    (*iOutput)->sendDef (stream);
  }
}