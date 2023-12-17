#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include "core.h"
#include "renderer.h"

class Window;
struct WindowedComponent;

enum class GUIRuntimeMode { Dynamic, Static };

/**
 * Keeps track of which window is visible. Changes state in response
 * to input events and propagates inputs to subwindows.
 *
 * Could possibly be extended to manage multiple windows on one screen,
 * or with overlapping panels.
 */
template <GUIRuntimeMode mode>
class WindowManager;


class WindowManagerBase {
public:
  WindowManagerBase(Graphics &g, ScreenDim const& dims, beer::List<Window> const& windows, beer::List<WindowedComponent> const& components);
  ~WindowManagerBase();
  /// Call this once per iteration of loop..
  void update();
  /// Create a new window and obtain handle to it
  // Window *createWindow();
  // template <typename Layout>
  // Window add(Layout const& layout);

  /// Change the currently displayed window to window with id.
  bool makeActive(beer::uint id);

  /// Calling this makes the whole GUI respond to an event
  void onEvent(InputEvent const &event);

  Graphics &getGraphics() const;
  beer::uint getWidth() const { return _dim.width; }
  beer::uint getHeight() const { return _dim.height; }

  /// Not to be called directly. Window::addComponent() uses this to register
  /// index.
  // beer::uint registerComponent(Window *win, WindowedComponent const &component);

  WindowedComponent *componentAt(beer::uint idx);

  Window *getWindow(beer::uint idx) {
    if (idx < _windows.size()) {
      return &_windows[idx];
    } else {
      return nullptr;
    }
  }

protected:
  Graphics &_graphics;
  beer::List<Window> const& _windows;
  beer::List<WindowedComponent> const& _components;
  const ScreenDim _dim;
  int _active_window = -1;
  int _next_window = -1;
};

template<>
class WindowManager<GUIRuntimeMode::Dynamic> : public WindowManagerBase {
  public:
    WindowManager(Graphics &g, ScreenDim const& dims) : WindowManagerBase(g, dims, v_windows, v_components), v_windows(), v_components() {} //TODO might not need explicit init of windows and components
    Window *createWindow();
    bool addComponent(beer::uint index, WindowedComponent const &component); //TODO bool with failure if too much memory used
  private:
    beer::Vector<Window> v_windows;
    beer::Vector<WindowedComponent> v_components;
};

using DynamicWM = WindowManager<GUIRuntimeMode::Dynamic>;

#endif // WINDOWMANAGER_H_
