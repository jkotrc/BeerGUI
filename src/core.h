#ifndef CORE_H_
#define CORE_H_

#ifndef BEER_ARDUINO
#include <cstring>
// #include <cstdint>
#endif

namespace beer {
using uint = unsigned int;

template <typename T> class List {
public:
  List(beer::uint size) {
    _buf = new T[size];
    _capacity = size;
    _size = 0;
  }
  List(List const &other) {
    _capacity = 2*other._size;
    _size = other._size;
    _buf = new T[_capacity];
    memcpy(_buf, other._buf, _size*sizeof(T));
  }
  List(List&& other) {
    _buf = other._buf;
    _capacity = other._capacity;
    _size = other._size;
  }
  List() : List(10) {}
  ~List() { delete[] _buf; }
  void push_back(T&& value) {
    if (_size < _capacity) {
      _buf[_size] = static_cast<T&&>(value);
      _size++;
    } else {
      T *newbuf = new T[_size * 2];
      memcpy(newbuf, _buf, _size * sizeof(T));
      delete[] _buf;
      _buf = newbuf;
      _buf[_size] = static_cast<T&&>(value);
      _size++;
    }
  }
  void push_back(T const &value) {
    if (_size < _capacity) {
      _buf[_size] = value;
      _size++;
    } else {
      T *newbuf = new T[_size * 2];
      memcpy(newbuf, _buf, _size * sizeof(T));
      delete[] _buf;
      _buf = newbuf;
      _buf[_size] = value;
      _size++;
    }
  }
  T &operator[](size_t index) { return _buf[index]; }
  beer::uint size() const { return _size; }

private:
  T *_buf = nullptr;
  beer::uint _size = 0;
  beer::uint _capacity = 0;
};
} // namespace beer

/**
 * TBA variable text sizes
 */
enum class TextSize { SMALL = 0, MEDIUM, LARGE };

/**
 * May later be extended for other event types,
 * but for now only take three basic signals
 */
enum class InputEvent { PLUS, MINUS, SELECT };

struct Color {
  beer::uint r;
  beer::uint g;
  beer::uint b;
};

/// Point on the screen with (0,0) at top left and +y down.
struct Point {
  Point(beer::uint x, beer::uint y) : x(x), y(y) {}
  Point(Point const& other) : x(other.x), y(other.y) {}
  Point& operator=(Point const& other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  Point operator+(Point const& other) {
    return {x+other.x, y+other.y};
  }
  Point& operator+=(Point const& other) {
    x += other.x;
    y += other.y;
    return *this;
  }
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
  Region() : top_left({0, 0}), bottom_right({0, 0}) {}
  Region(Point const &tl, Point const &br) : top_left(tl), bottom_right(br) {}
  Region operator+(Region const& other) {
    return {top_left+other.top_left, bottom_right+other.bottom_right};
  }
  Point top_left;
  Point bottom_right;
};

/// return true if point is in region
bool pointInRegion(Region const &reg, Point const &point);
/// return true if given regions overlap
bool regionsOverlap(Region const &reg1, Region const &reg2);
/**
 * Convert Color to 16 bit unsigned integer
 * with RGB565 format.
 */
beer::uint colorToInt565(Color const &color);

#endif // CORE_H_
