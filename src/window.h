#ifndef WINDOW_H_
#define WINDOW_H_

#include "windowmanager.h"
#include "component.h"


class Window {
    public:
        Window(beer::uint width, beer::uint height);
        ~Window();
        // Window(Window const& win);
        /// Add component to window, with anchor point relative to window's top left corner
        bool addComponent(Component* component);
        /// Draw all components in this window
        void draw();
        /// Calling this propagates the event to children, changing state
        void onEvent(InputEvent const& event);
        void setParent(WindowManager* parent);
        beer::uint getWidth() const;
        beer::uint getHeight() const;
    private:
      enum class CursorState {WINDOW,COMPONENT};
      Component **_components; // TODO support multiple components
      beer::uint _ncomponents = 0;
      beer::uint _cursor_pos = 0;
      CursorState _cursor_state = CursorState::WINDOW;
      Region _region;
      WindowManager *_parent;
};


#endif // WINDOW_H_
