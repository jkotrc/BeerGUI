#include "button.h"

using namespace beer;

ButtonComponent::ButtonComponent(Point const &dimensions, Action action) : _action(action) {
    _region = {{0,0}, {dimensions.x,dimensions.y}};
}

void ButtonComponent::handleEvent(InputEvent const &event_type) {}

void ButtonComponent::draw(Graphics &g) {
    // const Color button_color = _hover ? active_color : Color{0x00, 0xFF, 0x7F};
    const Color active = Color{0x00,0xFF,0x7F};

    Region inner = {_region.top_left+Point{1,1}, _region.bottom_right-Point{1,1}};

    g.fill(_region, active);
    if (!_hover)
        g.fill(inner, {0,0,0});
}

void ButtonComponent::activate() {
    _action();
}
