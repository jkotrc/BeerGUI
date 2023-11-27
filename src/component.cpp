#include "component.h"

using namespace beer;

Component::~Component() {
    //TODO call destructors on all children
}

void Component::setVisible(bool visible) {
    _isVisible = visible;
}

void Component::setHover(bool hover) {
    _hover = hover;
}

void Component::activate() {
    _active = true;
}

void Component::setCursorAt(bool cur) {
    _active = cur;
}

bool Component::isVisible() const {
    return _isVisible;
}

bool Component::isActive() const {
    return _active;
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
            _active = false; //setting _active to false surrenders control
            break;
    }

}

constexpr Color active_color = Color{0xaa, 0xaa, 0xff};

void SliderComponent::draw(Graphics& g) {
    Region head;
    const uint head_width = 10; //TODO make this configurable
    const uint basex = _region.top_left.x + (getWidth() *  _progress) / 255;
    const Color slider_color = _hover ? active_color : Color{0xff, 0xff, 0xff};

    head.top_left = {basex - head_width, _region.top_left.y};
    head.bottom_right = {basex + head_width, _region.bottom_right.y};
    g.fill(_region, slider_color);
    g.fill(head, {255, 0, 0});
}

ButtonComponent::ButtonComponent(Region const &region, ButtonFunc action) : _action(action) {
    _region = region;
}

void ButtonComponent::handleEvent(InputEvent const &event_type) {
    if (event_type == InputEvent::SELECT) {
        _action(this);
    }
}

void ButtonComponent::draw(Graphics &g) {
    const Color button_color = _hover ? active_color : Color{0x00, 0xFF, 0x7F};
    g.fill(_region, button_color);
}
