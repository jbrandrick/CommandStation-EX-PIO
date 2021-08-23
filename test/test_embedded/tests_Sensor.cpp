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
  sensorData.threshold  = 25;
  sensorData.type       = SENSOR_TYPE::ANALOG;

  RUN_TEST (testSensor_populate_with_sensordata);
  RUN_TEST (testSensor_populate_with_fields);
}


void testSensor_populate_with_sensordata () {
  sensor->populate (sensorData);
  TEST_ASSERT_TRUE (
      sensor->data.snum       == 1    &&
      sensor->data.pin        == 2    &&
      sensor->data.pullUp     == HIGH &&
      sensor->data.threshold  == 25   &&
      sensor->data.type       == SENSOR_TYPE::ANALOG
  );
}

void testSensor_populate_with_fields () {
  sensor->populate (SENSOR_TYPE::DIGITAL, 2, 3, 0);
  TEST_ASSERT_TRUE (
      sensor->data.snum       == 2    &&
      sensor->data.pin        == 3    &&
      sensor->data.pullUp     == LOW  &&
      sensor->data.threshold  == 0    &&
      sensor->data.type       == SENSOR_TYPE::DIGITAL
  );
}