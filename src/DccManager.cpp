#include "DccManager.h"

DccManager* DccManager::GetInstance () {
  if (dccManager == nullptr)
    dccManager = new DccManager ();

  return dccManager;
}