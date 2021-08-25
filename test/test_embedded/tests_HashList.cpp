#include <arduino.h>
#include <unity.h>
#include "tests_HashList.h"
#include "HashList.cpp"
#include "StringFormatter.h"

extern char *__brkval;
extern char *__malloc_heap_start;
void printFreeMemory () {
  char top;
  int freeMemory = __brkval ? &top - __brkval : &top - __malloc_heap_start;
  StringFormatter::send(Serial, F("Free memory=%d\n"), freeMemory);
}


HashList<TestValue>* list;

void testHashList () {
  list = new HashList<TestValue>;
  printFreeMemory ();
                                            // create & free 3 int[100] arrays
  for (int i=0; i < 100; i++) {             // do this 100 times
      RUN_TEST (testHashList_empty_get);
      RUN_TEST (testHashList_empty_hashlist);
      RUN_TEST (testHashList_add_to_hashlist);
      RUN_TEST (testHashList_remove_from_hashlist);
      RUN_TEST (testHashList_empty_hashlist);
    }
  printFreeMemory ();                       // memory should reduce by 600 + a few bytes (3 * 100 * 2)
}


void testHashList_empty_get () {
  TEST_ASSERT_NULL (list->get (1));
}

void testHashList_empty_hashlist () {
  TEST_ASSERT_EQUAL (0, list->size ());
}

void testHashList_add_to_hashlist () {
  list->getOrAdd (1);
  int ref1[] = {1};
  TEST_ASSERT_TRUE (testHashList_compare_keys (ref1, list));
  TEST_ASSERT_EQUAL (1, list->size ());

  list->getOrAdd (2);
  int ref2[] = {1, 2};
  TEST_ASSERT_TRUE (testHashList_compare_keys (ref2, list));

  list->getOrAdd (3);
  int ref3[] = {1, 2, 3};
  TEST_ASSERT_TRUE (testHashList_compare_keys (ref3, list));
}

void testHashList_remove_from_hashlist () {
  list->remove (2);
  int ref1[] = {1, 3};
  TEST_ASSERT_TRUE (testHashList_compare_keys (ref1, list));

  list->remove (3);
  int ref2[] = {1};
  TEST_ASSERT_TRUE (testHashList_compare_keys (ref2, list));

  list->remove (1);
  int ref3[] = {};
  TEST_ASSERT_TRUE (testHashList_compare_keys (ref3, list));
}



bool testHashList_compare_keys (int ref[], HashList<TestValue>* list) {
  // if (sizeof(*ref) != list->size ())
  //   return false;
  int refIdx = 0;
  bool result = true;
  list->walkList ([ref, refIdx, result] (int key, TestValue* testValue) mutable {
    if (ref[refIdx] != key)
      result = false;
    refIdx++;
  });

  return result;
}