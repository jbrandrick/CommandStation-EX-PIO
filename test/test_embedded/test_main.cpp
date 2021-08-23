#include <arduino.h>
#include <unity.h>

#include "tests_HashList.h"
#include "tests_Turnout.h"
#include "tests_Sensor.h"
#include "tests_Output.h"

void setup () {
  pinMode (LED_BUILTIN, OUTPUT);

  delay (2000);

  UNITY_BEGIN ();

  testHashList ();
  testTurnout ();
  testSensor ();
  testOutput ();

  UNITY_END ();
}

void loop () {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}