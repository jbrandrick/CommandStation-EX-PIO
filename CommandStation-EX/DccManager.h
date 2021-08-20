#ifndef DccManager_h
#define DccManager_h

#if !defined(DCC_MANAGER) 
#define DCC_MANAGER DccManager::GetInstance()
#endif

#include "HashList.h"
#include "Turnout.h"
#include "Sensor.h"
#include "Output.h"

class DccManager {

  private:
  
    DccManager () {
      dccManager = nullptr;
    }

    static DccManager* dccManager;

  public:

    DccManager (DccManager& other) = delete;
    void operator= (const DccManager&) = delete;

    static DccManager* GetInstance ();

    void init ();

    HashList<Turnout>* turnouts;
    HashList<Sensor>* sensors;
    HashList<Output>* outputs;

    // Print* stream;
};

#endif