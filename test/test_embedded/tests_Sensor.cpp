#include <arduino.h>
#include <unity.h>
#include "tests_Sensor.h"

Sensor* sensor;
SensorData sensorData;

void testSensor () {
  sensor = new Sensor;
  sensorData.snum       = 1;
  sensorData.pin        = 2;
  sensorData.pullUp     = 1;

  RUN_TEST (testSensor_populate_with_sensordata);
  RUN_TEST (testSensor_populate_with_fields);
}


void testSensor_populate_with_sensordata () {
  sensor->populate (sensorData);
  TEST_ASSERT_TRUE (
      sensor->data.snum       == 1    &&
      sensor->data.pin        == 2    &&
      sensor->data.pullUp     == HIGH
  );
}

void testSensor_populate_with_fields () {
  sensor->populate (2, 3, 0);
  TEST_ASSERT_TRUE (
      sensor->data.snum       == 2    &&
      sensor->data.pin        == 3    &&
      sensor->data.pullUp     == LOW
  );
}