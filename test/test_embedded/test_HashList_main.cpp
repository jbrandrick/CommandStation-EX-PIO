#include "HashList.h"
#include "unity.h"

struct TestValue {
  int value;
};

void test_add_to_hashlist (HashList<TestValue>);
void test_remove_from_hashlist (HashList<TestValue>);
bool compare_keys (int [], HashList<TestValue>);

void test_add_to_hashlist (HashList<TestValue> list) {
  // list.getOrAdd (1);
  // int ref1[] = {1};
  // TEST_ASSERT_TRUE (compare_keys (ref1, list));

  // list.getOrAdd (2);
  // int ref2[] = {1, 2};
  // TEST_ASSERT_TRUE (compare_keys (ref2, list));

  // list.getOrAdd (3);
  // int ref3[] = {1, 2, 3};
  // TEST_ASSERT_TRUE (compare_keys (ref3, list));
}

void test_remove_from_hashlist (HashList<TestValue> list) {
  // list.remove (2);
  // int ref1[] = {1, 3};
  // TEST_ASSERT_TRUE (compare_keys (ref1, list));

  // list.remove (3);
  // int ref2[] = {1};
  // TEST_ASSERT_TRUE (compare_keys (ref2, list));

  // list.remove (1);
  // int ref3[] = {};
  // TEST_ASSERT_TRUE (compare_keys (ref3, list));
}

int main()
{
  UNITY_BEGIN ();

  HashList<TestValue> list;
  TEST_ASSERT_EQUAL (0, list.size ());

  list.get (1);

  test_add_to_hashlist (list);
  test_remove_from_hashlist (list);

  UNITY_END ();

  return 0;
}

bool compare_keys (int ref[], HashList<TestValue> list) {
  int refIdx = 0;

  for ( HashList<TestValue>::Iterator iterator (list.begin ());
                                iterator.hasNext ();
                                iterator.next ()) {
    if (ref[refIdx] != iterator.key ())
      return false;
    refIdx++;
  }

  return true;
}