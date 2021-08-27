#include <unity.h>
#include "tests_DccManager.h"

void testDccManager () {
  RUN_TEST (testDccManager_getInstance);
  RUN_TEST (testDccManager_init);
}


void testDccManager_getInstance () {
  DccManager* dccManager1 = DCC_MANAGER;
  DccManager* dccManager2 = DCC_MANAGER;
  TEST_ASSERT_EQUAL (dccManager1, dccManager2);
}

void testDccManager_init () {
  DCC_MANAGER->init ();
  TEST_ASSERT_EQUAL (DCC_MANAGER->turnouts->size (), 0);
  TEST_ASSERT_EQUAL (DCC_MANAGER->sensors->size (), 0);
  TEST_ASSERT_EQUAL (DCC_MANAGER->outputs->size (), 0);
}