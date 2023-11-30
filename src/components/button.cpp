#include "button.h"

using namespace beer;

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
