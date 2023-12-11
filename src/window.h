#ifndef WINDOW_H_
#define WINDOW_H_

#include "component.h"
#include "core.h"
#include "windowmanager.h"

struct WindowedComponent {
  WindowedComponent() : position({0, 0}), cmp(nullptr) {}
  // ~WindowedComponent() { delete cmp; } //TODO shared pointer would be useful
  // here
  WindowedComponent(Point const &pos, Component *cmp)
      : position(pos), cmp(cmp) {}
  WindowedComponent(WindowedComponent const &other)
      : position(other.position), cmp(other.cmp) {}
  WindowedComponent &operator=(WindowedComponent const &other) {
    position = other.position;
    cmp = other.cmp;
    return *this;
  }
  Point position;
  Component *cmp;
};

/*
 * Component draws with graphics as if the origin point was the anchor.
 *
 * Then when window draw is called, window has an overriden graphics
 * instance with the correct offset and errors if draw would escape
 * the component's region
 *
 * TODO make a logger interface to stdout or serial
 *
 */

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
   * `drawPixel({0,0},color)` will be at top-left corner.
   */
  void setRegion(Region const &region);

  WindowGraphics(Graphics &g);
  void drawPixel(Point const &point, Color const &color) override;
  void fill(Region const &region, Color const &color) override;
  void drawLine(Point const &from, Point const &to, Color const &color) override;
  void update() override;
  void drawText(Point const &anchor, const char *text, Color const &color) override;

private:
  Region _region;
  Graphics &_graphics;
};

/**
 * A handle object representing a window inside the WindowManager. Not
 * to be created directly, essentially a part of WindowManager so far.
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
  /// Add component to window, with anchor point relative to window's top left
  /// corner
  bool addComponent(WindowedComponent const &component); // TODO rvalue??
  /// Draw all components in this window
  void draw();
  /// Calling this propagates the event to children, changing state
  void onEvent(InputEvent const &event);
  void setParent(WindowManager *parent);
  beer::uint getWidth() const;
  beer::uint getHeight() const;

private:
  // friend class WindowManager;
  enum class CursorState { WINDOW, COMPONENT };
  WindowManager *_parent = nullptr;
  beer::List<WindowedComponent *>
      _components; // TODO support multiple components
  beer::uint _cursor_pos = 0;
  CursorState _cursor_state = CursorState::WINDOW;
  Region _region;
  WindowGraphics *_graphics = nullptr;
  int _index = -1;
};

#endif // WINDOW_H_
