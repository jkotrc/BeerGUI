#include "window.h"

using namespace beer;

#define MAX_COMPONENTS 10

Window::Window(uint width, uint height) : _region({{0,0}, {width, height}}), _parent(nullptr), _components(nullptr), _ncomponents(0) {

}


Window::~Window() {
    delete _components;
}

bool Window::addComponent(Component* component) {
    if (component == nullptr) return false;
    component->setVisible(true);
    if (_components == nullptr) {
        _components = new Component*[MAX_COMPONENTS];
        _components[0] = component;
        _ncomponents = 1;
        component->setHover(true);
        return true;
    } else if (_ncomponents < MAX_COMPONENTS) {
        _components[_ncomponents] = component;
        _ncomponents++;
        return true;
    } else {
        return false;
    }
}

void Window::draw() {
    for (uint i = 0; i < _ncomponents; i++) {
        if (_components[i]->isVisible())
            _components[i]->draw(_parent->getGraphics());
    }
}

void Window::onEvent(InputEvent const& event) {
    if (_cursor_state == CursorState::WINDOW) {
        _components[_cursor_pos]->setHover(false);
        switch(event) {
            case (InputEvent::MINUS):
                if (_cursor_pos == 0) {
                    _cursor_pos = _ncomponents-1;
                } else {
                    _cursor_pos--;
                }
                break;
            case (InputEvent::PLUS):
                if (_cursor_pos + 1 >= _ncomponents) {
                    _cursor_pos = 0;
                } else {
                    _cursor_pos++;
                }
                break;
            case (InputEvent::SELECT):
                _cursor_state = CursorState::COMPONENT;
                _components[_cursor_pos]->activate();
                break;
        }
        _components[_cursor_pos]->setHover(true);
    } else {
        _components[_cursor_pos]->handleEvent(event);
        if (!_components[_cursor_pos]->isActive()) {
            _cursor_state = CursorState::WINDOW;
            _cursor_pos = 0;
        }
        // for (uint i = 0; i < _ncomponents; i++) {
        //     _components[i]->handleEvent(event);
        // }
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
