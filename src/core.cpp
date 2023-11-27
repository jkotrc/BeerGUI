#include "core.h"

bool pointInRegion(Region const &reg, Point const &point) {
  return (point.x <= reg.bottom_right.x && reg.top_left.x <= point.x) &&
         (point.y <= reg.bottom_right.y && reg.top_left.y <= point.y);
}
bool regionsOverlap(Region const &reg1, Region const &reg2) { return true; }
