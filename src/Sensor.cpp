#include "Sensor.h"
#include "StringFormatter.h"


void Sensor::populate (SensorData data) {
  populate ( data.snum, data.pin, data.pullUp, data.threshold, data.type );
}


void Sensor::populate ( int snum, int pin, int pullUp, int threshold = 0, SENSOR_TYPE type = DIGITAL) {
  data.type       = type;
  data.snum       = snum;
  data.pin        = pin;
  data.pullUp     = ( pullUp == 0 ? LOW : HIGH );
  data.threshold  = threshold;

  if ( data.type == ANALOG ) {
    analogWrite ( pin, pullUp );   // ????? don't use Arduino's internal pull-up resistors for
                                   // external infrared sensors
                                   // each sensor must have its own 1K external pull-up resistor
  }

  if ( data.type == DIGITAL ) {
    pinMode ( pin, INPUT );         // set mode to input
    digitalWrite ( pin, pullUp );   // don't use Arduino's internal pull-up resistors for
                                    // external infrared sensors
                                    // each sensor must have its own 1K external pull-up resistor
  }
}


bool Sensor::read () {
  if ( data.type == DIGITAL ) return !digitalRead ( data.pin );

  if ( data.type == ANALOG ) return ( analogRead ( data.pin ) < data.threshold );
  
  return false;
}


void Sensor::check ( Print *stream ) {
  bool currentState = read ();

  if ( currentState == active ) {

    if ( latchdelay != 0 ) {        // state changed back so reset count of data points
      // enable if you want to debug contact jitter
      //if (stream != NULL) StringFormatter::send(stream, F("JITTER %d %d\n"), 
      //                                          latchdelay, data.id);
       latchdelay = 0;
    }

  } else if ( latchdelay < 127 ) {  // state still changed so collect data points to smooth jitter
    latchdelay++;

  } else {                          // state changed and data in is good
    active  = currentState;
    latchdelay  = 0;

    if ( stream != NULL ) {
      send ( stream );
    }
  }
}


void Sensor::send ( Print *stream ) {
  StringFormatter::send ( stream, F("<%c %d>\n"), active ? 'Q' : 'q', data.snum );
}

void Sensor::sendDef ( Print *stream ) {
  StringFormatter::send ( stream, F("<Q %d %d %d>\n"), data.snum, data.pin, data.pullUp);
}