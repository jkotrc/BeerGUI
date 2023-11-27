#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include "core.h"

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
        WindowManager(unsigned int width, unsigned int height);
        /// Call this in your setup() to prepare display code.
        void setup();
        /// Add a window by ID. Preferably use an enum for this
        void add(int id, Window&& window);
        /// Change the currently displayed window to window with id.
        bool makeActive(int id);

    private:

};

#endif // WINDOWMANAGER_H_
