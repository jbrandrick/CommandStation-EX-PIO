#ifndef DccManager_h
#define DccManager_h

#include "HashList.h"
#include "Sensor.h"

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

    // HashList<Output> outputs;
    HashList<Sensor> sensors;
    // HashList<Turnout> turnouts;

    // Print* stream;

    Sensor* getOrAddSensor (int);
};

#endif