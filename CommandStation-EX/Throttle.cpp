#include "Throttle.h"

void Throttle::setFn (int16_t functionNumber, bool setOn) {
  unsigned long funcmask = (1UL << functionNumber);
  if (setOn) {
      functions |= funcmask;
  } else {
      functions &= ~funcmask;
  }
  updateGroupflags (functionNumber);
}
