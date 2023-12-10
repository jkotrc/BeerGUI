#include "slider.h"

using namespace beer;

SliderComponent::SliderComponent(Region const& region, uint initial_progress) : _progress((initial_progress)) {
    _region = region;

}

void SliderComponent::handleEvent(InputEvent const& event_type) {
    switch(event_type) {
        case(InputEvent::MINUS):
            if (_progress > 5) {
                _progress-=5;
            }
            break;
        case(InputEvent::PLUS):
            if (_progress < 250) {
                _progress+=5;
            }
            break;
        case(InputEvent::SELECT):
            _active = false; //setting _active to false surrenders control
            break;
    }

}

void SliderComponent::draw(Graphics& g) {
    Region head;
    Region bob;
    const uint head_width = 4; //TODO make this configurable
    const uint basex = _region.top_left.x + (getWidth() *  _progress) / 255;

    // const Color slider_color = _hover ? active_color : Color{0xff, 0xff, 0xff};

    head.top_left = {basex - head_width, _region.top_left.y};
    head.bottom_right = {basex + head_width, _region.bottom_right.y};
    g.fill(_region, {255,255,255});
    g.fill(head, {0, 0, 0});
    if (_hover) {
        bob = head; //TODO point operators
        bob.top_left.x += 1;
        bob.bottom_right.x -= 1;
        bob.bottom_right.y -= 1;
        g.fill(bob, {255,255,255});
    }
}
