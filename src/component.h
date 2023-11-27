#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "core.h"
#include "renderer.h"

class Window;

/**
 *
 *
 */
class Component {
    public:
        virtual void handleEvent(InputEvent const& event_type) = 0;
        virtual void draw(Graphics const& graphics) = 0;
        void setVisible(bool visible);
    private:
        Component* children;
        Region _region;
        bool _isVisible;
        bool _cursorable; //Whether cursor should stop at this component
        Window* _parent;
};

//TODO move to components/slidercomponent.h for clearer separation
class SliderComponent : Component {
    public:
        SliderComponent(uint8_t initial_progress);
        void handleEvent(InputEvent const& event_type) override;
        void draw(Graphics const& graphics) override;
    private:
        uint8_t _progress;


};

namespace internal {

}



#endif // COMPONENT_H_
