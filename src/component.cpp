#include "component.h"

using namespace beer;

Component::~Component() {
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

Region Component::getRegion() const {
    return _region;
}
