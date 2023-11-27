#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "core.h"
#include "renderer.h"

class Window;

/**
 * Base class for components. Each new components should derive from this
 * and provide their own code for drawing and handling user input.
 */
class Component {
    public:
        virtual ~Component();
        virtual void handleEvent(InputEvent const& event_type) = 0;
        virtual void draw(Graphics& graphics) = 0;
        void setVisible(bool visible);
        void setCursorAt(bool cursor_on_component);

        beer::uint getWidth() const;
        beer::uint getHeight() const;
    protected:
        Component* children;
        Region _region;
        bool _isVisible;
        bool _cursorable; //Whether cursor should stop at this component
        bool _active;
        Window* _parent;
};

//TODO move to components/slidercomponent.h for clearer separation
class SliderComponent : public Component {
    public:
        SliderComponent(Region const& region, uint8_t initial_progress);
        void handleEvent(InputEvent const& event_type) override;
        void draw(Graphics& graphics) override;
    private:
        uint8_t _progress;
};

namespace internal {

}



#endif // COMPONENT_H_
