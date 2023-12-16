#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include "core.h"
#include "renderer.h"

class Window;
struct WindowedComponent;

/**
 * Keeps track of which window is visible. Changes state in response
 * to input events and propagates inputs to subwindows.
 *
 * Could possibly be extended to manage multiple windows on one screen,
 * or with overlapping panels.
 */
class WindowManager {
public:
  WindowManager(Graphics &g, beer::uint width, beer::uint height);
  ~WindowManager();
  /// Call this once per iteration of loop..
  void update();
  /// Create a new window and obtain handle to it
  Window *createWindow();
  // template <typename Layout>
  // Window add(Layout const& layout);

  /// Change the currently displayed window to window with id.
  bool makeActive(beer::uint id);

  /// Calling this makes the whole GUI respond to an event
  void onEvent(InputEvent const &event);

  Graphics &getGraphics() const;
  beer::uint getWidth() const { return _width; }

  /// Not to be called directly. Window::addComponent() uses this to register
  /// index.
  beer::uint registerComponent(Window *win, WindowedComponent const &component);

  WindowedComponent *componentAt(beer::uint idx);

  Window *getWindow(beer::uint idx) {
    if (idx < _windows.size()) {
      return &_windows[idx];
    } else {
      return nullptr;
    }
  }

private:
  Graphics &_graphics;
  beer::List<WindowedComponent> _components;
  beer::List<Window> _windows;
  beer::uint _width; // TODO dimensions type
  beer::uint _height;
  int _active_window = -1;
  int _next_window = -1;
};

#endif // WINDOWMANAGER_H_
