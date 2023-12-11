#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include "core.h"
#include "renderer.h"
class Window;
struct WindowedComponent;

/**
 * WIP:
 * Keeps track of which window is visible. Changes state in response
 * to input events and propagates inputs to subwindows.
 *
 * Could possibly be extended to manage multiple windows on one screen,
 * or with overlapping panels.
 */
class WindowManager {
    public:
        WindowManager(Graphics& g, beer::uint width, beer::uint height);
        ~WindowManager();
        /// Call this once per iteration of loop..
        void update();
        /// Create a new window and obtain handle to it
        Window* add();
        //TODO
        // template <typename Layout>
        // Window add(Layout const& layout);

        /// Change the currently displayed window to window with id.
        bool makeActive(beer::uint id);

        /// Calling this makes the whole GUI respond to an event
        void onEvent(InputEvent const& event);

        Graphics& getGraphics() const;

        /// Not to be called directly. Window can have components added to it, but doesn't directly own the component
        WindowedComponent* registerComponent(Window* win, WindowedComponent const& component);
    private:
        Graphics& _graphics;
        beer::List<WindowedComponent> _components;
        beer::List<Window> _windows;
        beer::uint _width; //TODO dimensions type
        beer::uint _height;
        int _active_window;
};

#endif // WINDOWMANAGER_H_
