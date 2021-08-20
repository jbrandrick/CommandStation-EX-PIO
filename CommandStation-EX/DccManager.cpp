#include "DccManager.h"

DccManager* DccManager::GetInstance () {
  if (dccManager == nullptr)
    dccManager = new DccManager ();

  return dccManager;
}


void DccManager::init () {
  turnouts = new HashList<Turnout>;
  sensors = new HashList<Sensor>;
  outputs = new HashList<Output>;
}