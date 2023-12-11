#ifndef SLIDER_H_
#define SLIDER_H_

#include "component.h"

class SliderComponent : public Component {
    public:
        SliderComponent(Point const& dimensions, beer::uint initial_progress);
        void handleEvent(InputEvent const& event_type) override;
        void draw(Graphics& graphics) override;
    protected:
        Point _dimensions;
        beer::uint _progress;
        bool _cursorable = true;
};

#endif // SLIDER_H_
