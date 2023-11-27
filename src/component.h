#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "core.h"
#include "renderer.h"

class Window;

/**
 * Base class for components. Each new component should derive from this
 * and provide code for drawing and handling user input.
 *
 * Focus is managed by parent window, so `handleEvent` is not called if
 * the cursor is not at the component.
 */
class Component {
    public:
        virtual ~Component();
        virtual void handleEvent(InputEvent const& event_type) = 0;
        virtual void draw(Graphics& graphics) = 0;
        void setVisible(bool visible);
        void setHover(bool hover);
        void activate();
        void setCursorAt(bool cursor_on_component);

        bool isVisible() const;
        bool isActive() const;
        beer::uint getWidth() const;
        beer::uint getHeight() const;
    protected:
        Region _region;
        bool _isVisible = false;
        bool _cursorable = false; //Whether cursor should stop at this component
        bool _hover = false; //Whether cursor is hovering
        bool _active = false;
        Window* _parent = nullptr;
};

//TODO move to components/slidercomponent.h for clearer separation
class SliderComponent : public Component {
    public:
        SliderComponent(Region const& region, uint8_t initial_progress);
        void handleEvent(InputEvent const& event_type) override;
        void draw(Graphics& graphics) override;
    protected:
        uint8_t _progress;
        bool _cursorable = true;
};


class ButtonComponent : public Component {
    public:
        using ButtonFunc = void (*)(Component*);
        ButtonComponent(Region const& region, ButtonFunc action);
        void handleEvent(InputEvent const& event_type) override;
        void draw(Graphics& graphics) override;
    private:
        ButtonFunc _action;
        uint8_t _progress;
};


namespace internal {

}



#endif // COMPONENT_H_
