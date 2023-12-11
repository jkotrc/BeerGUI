#include "core.h"
#include "window.h"

using namespace beer;

#define MAX_COMPONENTS 10

WindowGraphics::WindowGraphics(Graphics& g) : _graphics(g) {}
void WindowGraphics::setRegion(Region const& region) {
    _region = region;
}
void WindowGraphics::update() { _graphics.update(); }

//TODO complete error checking in WindowGraphics rendering functions

void WindowGraphics::drawPixel(Point const& point, Color const& color) {
    const Point& origin = _region.top_left;
    if (!pointInRegion(_region, point)) {
        //TODO: log error
        return;
    }
    _graphics.drawPixel({origin.x+point.x, origin.y+point.y}, color);
}

void WindowGraphics::fill(Region const& region, Color const& color) {
    const Point& origin = _region.top_left;
    Region offset_region({region.top_left.x+origin.x,region.top_left.y+origin.y},
                         {region.bottom_right.x+origin.x,region.bottom_right.y+origin.y});

    _graphics.fill(offset_region,color);
}

void WindowGraphics::drawLine(Point const& from, Point const& to, Color const& color) {
    // _graphics.drawLine(from,to,color);

}

void WindowGraphics::drawText(Point const& anchor, const char* text, Color const& color) {
    // _graphics.drawText(anchor,text,color);
}

Window::~Window() {

}

Window::Window() : _components() {

}

Window::Window(Window&& other)
: _parent(other._parent),
  _cursor_pos(other._cursor_pos),
  _cursor_state(other._cursor_state),
  _region(other._region),
  _graphics(other._graphics),
_components(other._components){}

Window& Window::operator=(Window&& other) {
    _parent = other._parent;
    _cursor_pos = other._cursor_pos;
    _cursor_state = other._cursor_state;
    _region = other._region;
    _graphics = other._graphics;
    return *this;
}

Window::Window(WindowManager* parent, beer::uint width, beer::uint height)
    : _parent(parent), _region({{0,0},{width,height}}) {
    _graphics = new WindowGraphics(_parent->getGraphics());
}

bool Window::addComponent(WindowedComponent const& component) {
    if (_parent == nullptr || component.cmp == nullptr) return false;
    _components.push_back(_parent->registerComponent(this, component));

    return true;
}

void Window::draw() {
    if (_graphics == nullptr) return;

    for (uint i = 0; i < _components.size(); i++) {
        if (_components[i]->cmp->isVisible()) {
            Region offset_region = _components[i]->cmp->getRegion();
            offset_region.top_left += _components[i]->position;
            offset_region.bottom_right += _components[i]->position;
            _graphics->setRegion(offset_region);
            _components[i]->cmp->draw(*_graphics);
        }
    }
}

//TODO cursorable
void Window::onEvent(InputEvent const& event) {
    if (_cursor_state == CursorState::WINDOW) {
        _components[_cursor_pos]->cmp->setHover(false);
        switch(event) {
            case (InputEvent::MINUS):
                if (_cursor_pos == 0) {
                    _cursor_pos = _components.size()-1;
                } else {
                    _cursor_pos--;
                }
                break;
            case (InputEvent::PLUS):
                if (_cursor_pos + 1 >= _components.size()) {
                    _cursor_pos = 0;
                } else {
                    _cursor_pos++;
                }
                break;
            case (InputEvent::SELECT):
                _cursor_state = CursorState::COMPONENT;
                _components[_cursor_pos]->cmp->activate();
                break;
        }
        _components[_cursor_pos]->cmp->setHover(true);
    } else {
        _components[_cursor_pos]->cmp->handleEvent(event);
        if (!_components[_cursor_pos]->cmp->isActive()) {
            _cursor_state = CursorState::WINDOW;
            _cursor_pos = 0;
        }
    }
}

void Window::setParent(WindowManager* parent) {
    _parent = parent;
}

beer::uint Window::getWidth() const {
    return _region.bottom_right.x-_region.top_left.x;
}
beer::uint Window::getHeight() const {
    return _region.bottom_right.y-_region.top_left.y;
}

WindowManager::WindowManager(Graphics& g, beer::uint width, beer::uint height)
    : _windows(), _components(), _graphics(g), _active_window(-1), _width(width),_height(height) {

}

WindowManager::~WindowManager() {

}

void WindowManager::update() {
    if (_active_window == -1) {
        // TODO log that no window in focus
        return;
    }
    _windows[_active_window].draw();
    _graphics.update();
}

Window* WindowManager::add() {
    _windows.push_back(Window{this, _width, _height});
    const uint current_idx = _windows.size() - 1;
    if (current_idx == 0)
        _active_window = current_idx;
    return &_windows[current_idx];
}

bool WindowManager::makeActive(beer::uint id) {
    if (id < _windows.size()) {
        _active_window = id;
        return true;
    }
    return false;
}

void WindowManager::onEvent(InputEvent const& event) {
    _windows[_active_window].onEvent(event);
}

Graphics& WindowManager::getGraphics() const {
    return _graphics;
}

WindowedComponent* WindowManager::registerComponent(Window* win, WindowedComponent const& component) {
    _components.push_back(component);
    return &_components[_components.size()-1];
}
