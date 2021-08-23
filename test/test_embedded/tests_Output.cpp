#include <arduino.h>
#include <unity.h>
#include "tests_Output.h"

Output* output;
OutputData outputData;

void testOutput () {
  output = new Output;
  outputData.oStatus  = 0;
  outputData.id       = 1;
  outputData.pin      = 2;
  outputData.iFlag    = 3;

  RUN_TEST (testOutput_populate_with_outputdata);
  RUN_TEST (testOutput_populate_with_fields);
}


void testOutput_populate_with_outputdata () {
  output->populate (outputData);
  TEST_ASSERT_TRUE (
      output->data.oStatus == 0  &&
      output->data.id      == 1  &&
      output->data.pin     == 2  &&
      output->data.iFlag   == 3
  );
}

void testOutput_populate_with_fields () {
  output->populate (2, 3, 4);
  TEST_ASSERT_TRUE (
      output->data.oStatus == 0  &&
      output->data.id      == 2  &&
      output->data.pin     == 3  &&
      output->data.iFlag   == 4
  );
}