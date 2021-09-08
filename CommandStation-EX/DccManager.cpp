#include "DccManager.h"

DccManager* DccManager::instance = nullptr;

DccManager* DccManager::getInstance () {
  if (instance == nullptr) {
    instance = new DccManager ();
    instance->init ();
  }
  return instance;
}

void DccManager::init () {
  eeStore = new EEStore;

  locos     = new HashList<Loco>;
  turnouts  = new HashList<Turnout>;
  sensors   = new HashList<Sensor>;
  outputs   = new HashList<Output>;

  currentSensorKey = -1;
}

// TODO remove the need to walk the list each time
void DccManager::checkSensor (Stream& stream) {
  if (sensors->size () > 0) {
    if (currentSensorKey == -1) {
      currentSensorKey = sensors->getFirstKey ();
    } else {
      currentSensorKey = sensors->getNextKey (currentSensorKey);
    }
    sensors->get (currentSensorKey)->check (&stream);
  }
}