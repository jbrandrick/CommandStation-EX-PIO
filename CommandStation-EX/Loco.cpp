#include "Loco.h"


// Set function to value on or off
void Loco::setFn (int16_t functionNumber, bool setOn) {
  unsigned long funcmask = (1UL << functionNumber);
  if (setOn) {
      functions |= funcmask;
  } else {
      functions &= ~funcmask;
  }
  updateGroupflags (functionNumber);
}


// Change function according to how button was pressed,
// typically in WiThrottle.
// Returns new state or -1 if nothing was changed.
int Loco::changeFn (int16_t functionNumber, bool pressed) {
  int funcstate = -1;
  if (functionNumber > 28)
    return funcstate;

  // Take care of functions:
  // Imitate how many command stations do it: Button press is
  // toggle but for F2 where it is momentary
  unsigned long funcmask = (1UL << functionNumber);
  if (functionNumber == 2) {
      // turn on F2 on press and off again at release of button
    if (pressed) {
      functions |= funcmask;
      funcstate = 1;
    } else {
      functions &= ~funcmask;
      funcstate = 0;
    }
  } else {
      // toggle function on press, ignore release
    if (pressed) {
      functions ^= funcmask;
    }
    funcstate = (functions & funcmask) ? 1 : 0;
  }
  updateGroupflags (functionNumber);

  return funcstate;
}

int Loco::getFn (int16_t functionNumber) {
  if (functionNumber > 28)
    return -1;

  unsigned long funcmask = (1UL << functionNumber);
  return (functions & funcmask)? 1 : 0;
}


// Set the group flag to say we have touched the particular group.
// A group will be reminded only if it has been touched.  
void Loco::updateGroupflags (int16_t functionNumber) {
  byte groupMask;

  if      (functionNumber <= 4)   groupMask = FN_GROUP_1;
  else if (functionNumber <= 8)   groupMask = FN_GROUP_2;
  else if (functionNumber <= 12)  groupMask = FN_GROUP_3;
  else if (functionNumber <= 20)  groupMask = FN_GROUP_4;
  else                            groupMask = FN_GROUP_5;

  groupFlags |= groupMask;
}
