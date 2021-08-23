#include <arduino.h>
#include <unity.h>
#include "tests_HashList.h"
#include "HashList.cpp"

HashList<TestValue>* list;

void testHashList () {
  list = new HashList<TestValue>;

  RUN_TEST (testHashList_empty_get);
  RUN_TEST (testHashList_empty_hashlist);
  RUN_TEST (testHashList_add_to_hashlist);
  RUN_TEST (testHashList_remove_from_hashlist);
  RUN_TEST (testHashList_empty_hashlist);
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
  int refIdx = 0;

  // if (sizeof(*ref) != list->size ())
  //   return false;

  for ( HashList<TestValue>::Iterator iterator (list->begin ());
                                iterator.hasNext ();
                                iterator.next ()) {
    if (ref[refIdx] != iterator.key ())
      return false;
    refIdx++;
  }

  return true;
}