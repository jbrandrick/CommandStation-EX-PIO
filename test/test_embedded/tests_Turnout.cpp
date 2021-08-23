#include <arduino.h>
#include <unity.h>
#include "tests_Turnout.h"

Turnout* turnout;
TurnoutData turnoutData;

void testTurnout () {
  turnout = new Turnout;

  RUN_TEST (testTurnout_populate_with_turnoutdata_DCC);
  RUN_TEST (testTurnout_populate_with_turnoutdata_PWM);
}


void testTurnout_populate_with_turnoutdata_DCC () {
  turnoutData.id          = 1;
  turnoutData.tStatus     = 0;
  turnoutData.subAddress  = 2;
  turnoutData.address     = 3;

  turnout->populate (turnoutData);
  TEST_ASSERT_TRUE (
      turnout->data.id          == 1  &&
      turnout->data.tStatus     == 0  &&
      turnout->data.subAddress  == 2  &&
      turnout->data.address     == 3
  );
}

void testTurnout_populate_with_turnoutdata_PWM () {
  turnoutData.id            = 2;
  turnoutData.tStatus       = STATUS_PWM | (3 & STATUS_PWMPIN);
  turnoutData.moveAngle     = 20;
  turnoutData.inactiveAngle = 30;

  turnout->populate (turnoutData);
  TEST_ASSERT_TRUE (
      turnout->data.id                        == 2          &&
      (turnout->data.tStatus & STATUS_PWM)    == STATUS_PWM &&
      (turnout->data.tStatus & STATUS_PWMPIN) == 3          &&
      turnout->data.moveAngle                 == 10         &&
      turnout->data.inactiveAngle             == 20
  );
}