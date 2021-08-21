#ifndef DccManager_h
#define DccManager_h

#if !defined(DCC_MANAGER) 
#define DCC_MANAGER DccManager::GetInstance()
#endif

#include "HashList.h"
#include "EEStore.h"
#include "Turnout.h"
#include "Sensor.h"
#include "Output.h"

class DccManager {

  private:

    DccManager () {
      dccManager = nullptr;
    }

    static DccManager* dccManager;

    HashList<Sensor>::Iterator iSensor;

  public:

    EEStore* eeStore;

    HashList<Turnout>* turnouts;
    HashList<Sensor>* sensors;
    HashList<Output>* outputs;

    DccManager (DccManager& other) = delete;
    void operator= (const DccManager&) = delete;

    static DccManager* GetInstance ();

    void init ();

    void printAllTurnouts (Print*);
    void sendDefTurnouts (Print*);
    void sendWifiTurnouts (RingStream*);

    void checkSensor (Stream&);
    void printAllSensors (Print*);
    void sendDefSensors (Print*);

    void printAllOutputs (Print*);
    void sendDefOutputs (Print*);
};

#endif