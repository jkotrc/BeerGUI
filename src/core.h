#ifndef CORE_H_
#define CORE_H_

#include <utility>
#include <cstdint>
#include <memory>

/**
 * TBA variable text sizes
 */
enum class TextSize {
  SMALL = 0,
  MEDIUM,
  LARGE
};

/**
 * May later be extended for other event types,
 * but for now only take three basic signals
 */
enum class InputEvent {
    PLUS,
    MINUS,
    SELECT
};

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

/// Point on the screen with (0,0) at top left and +y down.
struct Point {
    uint8_t x;
    uint8_t y;
};

/// "x" width and "y" height
using ScreenDim = Point;

/**
 * A portion of the screen defined by top left
 * and bottom right points. Each component reserves
 * its own non-overlapping region
 */
struct Region {
    Point top_left;
    Point bottom_right;
};

/// return true if point is in region
bool pointInRegion(Region const& reg, Point const& point);
/// return true if given regions overlap
bool regionsOverlap(Region const& reg1, Region const& reg2);

#endif // CORE_H_
