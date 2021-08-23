#include "HashList.h"

class TestValue {
  public:
    int value;
};

void testHashList ();
void testHashList_empty_get ();
void testHashList_empty_hashlist ();
void testHashList_add_to_hashlist ();
void testHashList_remove_from_hashlist ();

bool testHashList_compare_keys (int [], HashList<TestValue>*);