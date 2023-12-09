#ifndef CORE_H_
#define CORE_H_

#ifndef BEER_ARDUINO
 // #include <cstdint>
#endif

namespace beer {
  using uint = unsigned int;
}

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
  beer::uint r;
  beer::uint g;
  beer::uint b;
};

/// Point on the screen with (0,0) at top left and +y down.
struct Point {
    beer::uint x;
    beer::uint y;
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
/**
 * Convert Color to 16 bit unsigned integer
 * with RGB565 format.
 */
beer::uint colorToInt565(Color const& color);

#endif // CORE_H_
