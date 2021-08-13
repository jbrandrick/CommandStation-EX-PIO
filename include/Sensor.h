#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"

enum SENSOR_TYPE : byte {
  ANALOG,
  DIGITAL,
}; 

struct SensorData {
  int         snum;
  uint8_t     pin;
  uint8_t     pullUp;
  uint8_t     threshold;
  SENSOR_TYPE type;
};

class Sensor {
  public:
    bool active;
    byte latchdelay;

    SensorData data;

    Sensor () {
      active      = false;
      latchdelay  = 0;
    }

    void populate ( SensorData );
    void populate ( int, int, int, int, SENSOR_TYPE );
    void check ( Print * );
    void send ( Print * );
    void sendDef ( Print * );
    bool read ();
};

#endif