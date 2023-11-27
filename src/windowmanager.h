#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include "component.h"

class Window;


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
        /// Call this once per iteration of loop..
        void update();
        /// Add a window by ID. Preferably use an enum to name the different windows.
        void add(beer::uint id, Window const& window);
        /// Change the currently displayed window to window with id.
        bool makeActive(beer::uint id);
        /// Calling this propagates the event to children, changing state
        void onEvent(InputEvent const& event);

        Graphics& getGraphics() const;
    private:
        beer::uint _active_window;
        beer::uint _nwindows;
        Window* _windows;
        Graphics& _graphics;
};

#endif // WINDOWMANAGER_H_
