#ifndef SLIDER_H_
#define SLIDER_H_

#include "../component.h"

class SliderComponent : public Component {
    public:
        SliderComponent(Region const& region, uint8_t initial_progress);
        void handleEvent(InputEvent const& event_type) override;
        void draw(Graphics& graphics) override;
    protected:
        uint8_t _progress;
        bool _cursorable = true;
};


#endif // SLIDER_H_
