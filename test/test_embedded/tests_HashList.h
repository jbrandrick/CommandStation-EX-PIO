#include "HashList.h"

class TestValue {
  public:
    int value;
};

void testHashList ();
void test_empty_get ();
void test_empty_hashlist ();
void test_add_to_hashlist ();
void test_remove_from_hashlist ();

bool compare_keys (int [], HashList<TestValue>*);