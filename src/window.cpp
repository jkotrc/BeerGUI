#include "window.h"

using namespace beer;

Window::Window(uint width, uint height) : _region({{0,0}, {width, height}}), _parent(nullptr), _components(nullptr), _ncomponents(0) {

}


Window::~Window() {
    for (uint i = 0; i < _ncomponents; i++) {
        delete _components[i];
    }
    delete _components;
}

bool Window::addComponent(Component* component) {
    if (_components == nullptr) {
        _components = new Component*[1];
        _components[0] = component;
        _ncomponents = 1;
        return true;
    } else {
        return false;
    }

}

void Window::draw() {
    for (uint i = 0; i < _ncomponents; i++) {
        _components[i]->draw(_parent->getGraphics());
    }
}

void Window::onEvent(InputEvent const& event) {
    for (uint i = 0; i < _ncomponents; i++) {
        _components[i]->handleEvent(event);
    }
}

void Window::setParent(WindowManager* parent) {
    _parent = parent;
}

beer::uint Window::getWidth() const {
    return _region.bottom_right.x;
}
beer::uint Window::getHeight() const {
    return _region.bottom_right.y;
}
