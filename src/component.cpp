#include "component.h"

using namespace beer;

Component::~Component() {
    //TODO call destructors on all children
}

void Component::setVisible(bool visible) {
    _isVisible = visible;
}

void Component::setCursorAt(bool cur) {
    _active = cur;
}


beer::uint Component::getWidth() const {
    return _region.bottom_right.x - _region.top_left.x;
}
beer::uint Component::getHeight() const {
    return _region.bottom_right.y - _region.top_left.y;
}


SliderComponent::SliderComponent(Region const& region, uint8_t initial_progress) : _progress((initial_progress)) {
    _region = region;
}

void SliderComponent::handleEvent(InputEvent const& event_type) {
    switch(event_type) {
        case(InputEvent::MINUS):
            if (_progress > 0) {
                _progress-=5;
            }
            break;
        case(InputEvent::PLUS):
            if (_progress < 255) {
                _progress+=5;
            }
            break;
        case(InputEvent::SELECT):
            break;
    }

}

void SliderComponent::draw(Graphics& g) {
    g.fill(_region, {0xff, 0xff, 0xff});
    Region head;
    const uint head_width = 10; //TODO make this configurable
    const uint basex = _region.top_left.x + (getWidth() *  _progress) / 255;
    head.top_left = {basex - head_width, _region.top_left.y};
    head.bottom_right = {basex + head_width, _region.bottom_right.y};
    g.fill(head, {255, 0, 0});
}
