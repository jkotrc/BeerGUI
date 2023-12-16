#ifndef WINDOW_H_
#define WINDOW_H_

#include "component.h"
#include "core.h"
#include "windowmanager.h"

struct WindowedComponent {
  WindowedComponent() : position({0, 0}), cmp(nullptr) {}
  WindowedComponent(Point const &pos, Component *cmp)
      : position(pos), cmp(cmp) {}
  WindowedComponent(WindowedComponent const &other)
      : position(other.position), cmp(other.cmp) {}
  WindowedComponent(WindowedComponent &&other)
      : position(other.position), cmp(other.cmp) {}
  WindowedComponent &operator=(WindowedComponent const &other) {
    position = other.position;
    cmp = other.cmp;
    return *this;
  }
  WindowedComponent &operator=(WindowedComponent &&other) {
    position = other.position;
    cmp = other.cmp;
    return *this;
  }
  Point position;
  Component *cmp;
};

/**
 * A Graphics provider for window. Draws into a given Region at an offset,
 * For example, components are drawn by the parent window, which uses
 * WindowGraphics to safely draw the component. If the component tries to draw
 * outside its region, an error should be logged
 */
class WindowGraphics : public Graphics {
public:
  /**
   * Set the intended region to be drawn in for subsequent
   * draw function. All rendering methods will treat the top
   * left corner of the region as the origin point, so
   * `drawPixel({0,0},color)` will be at top-left corner of the currently set
   * region.
   */
  void setRegion(Region const &region);

  WindowGraphics(Graphics &g);
  void drawPixel(Point const &point, Color const &color) override;
  void fill(Region const &region, Color const &color) override;
  void drawLine(Point const &from, Point const &to,
                Color const &color) override;
  void update() override;
  void clear() override;
  void drawText(Point const &anchor, const char *text,
                Color const &color) override;

private:
  Region _region;
  Graphics &_graphics;
};

/**
 * The state of a window inside the WindowManager. Not
 * to be created directly. Once you create a WindowManager with a given
 * number of windows, they can be accessed using `manager.getWindow(index)`
 */
class Window {
public:
  ~Window();
  Window();
  // Window(Window const& other);
  Window(Window &&other);
  Window &operator=(Window &&other);
  Window(WindowManager *parent, beer::uint width, beer::uint height);
  // Window(Window const& win);
  /// Add component to window, with anchor point relative to window's top left corner
  bool addComponent(WindowedComponent const &component);
  /// Draw all components in this window
  void draw();
  /// Calling this propagates the event to children, changing state
  void onEvent(InputEvent const &event);
  void setParent(WindowManager *parent);
  beer::uint getWidth() const;
  beer::uint getHeight() const;

private:
  WindowedComponent *getComponent(beer::uint idx);
  enum class CursorState { WINDOW, COMPONENT };
  WindowManager *_parent = nullptr;
  beer::List<beer::uint> _components;
  beer::uint _cursor_pos = 0;
  CursorState _cursor_state = CursorState::WINDOW;
  Region _region;
  WindowGraphics *_graphics = nullptr;
  int _index = -1;
};

#endif // WINDOW_H_
