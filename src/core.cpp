#include "core.h"

using namespace beer;

bool pointInRegion(Region const &reg, Point const &point) {
  return (point.x <= reg.bottom_right.x && reg.top_left.x <= point.x) &&
         (point.y <= reg.bottom_right.y && reg.top_left.y <= point.y);
}
bool regionsOverlap(Region const &reg1, Region const &reg2) { return true; }

// TODO convert color construct to RGB565 format uesd in GFX
//  for now, just black for (0,0,0) or white for all other colors.
uint colorToInt565(Color const &color) {
  return !(color.r == 0 && color.g == 0 && color.b == 0);
}
