#include "window.h"
#include "core.h"

#ifndef BEER_LINUX
  #include <Arduino.h>
#endif

using namespace beer;

WindowGraphics::WindowGraphics(Graphics &g) : _graphics(g) {}
void WindowGraphics::setRegion(Region const &region) { _region = region; }
void WindowGraphics::update() { _graphics.update(); }
void WindowGraphics::clear() { _graphics.clear(); }

void WindowGraphics::drawPixel(Point const &point, Color const &color) {
  const Point &origin = _region.top_left;
  if (!pointInRegion(_region, point)) {
    // TODO: log error
    return;
  }
  _graphics.drawPixel({origin.x + point.x, origin.y + point.y}, color);
}

void WindowGraphics::fill(Region const &region, Color const &color) {
  const Point &origin = _region.top_left;
  Region offset_region(
      {region.top_left.x + origin.x, region.top_left.y + origin.y},
      {region.bottom_right.x + origin.x, region.bottom_right.y + origin.y});

  _graphics.fill(offset_region, color);
}

// TODO complete the next two WindowGraphics draw functions
void WindowGraphics::drawLine(Point const &from, Point const &to,
                              Color const &color) {
  // _graphics.drawLine(from,to,color);
}

void WindowGraphics::drawText(Point const &anchor, const char *text,
                              Color const &color) {
  // _graphics.drawText(anchor,text,color);
}

Window::~Window() {}

Window::Window() : _components(2) {}

Window::Window(Window &&other)
    : _parent(other._parent), _cursor_pos(other._cursor_pos),
      _cursor_state(other._cursor_state), _region(other._region),
      _graphics(other._graphics), _components(other._components) {}

Window &Window::operator=(Window &&other) {
  _parent = other._parent;
  _cursor_pos = other._cursor_pos;
  _cursor_state = other._cursor_state;
  _region = other._region;
  _graphics = other._graphics;
  _components = other._components;
  return *this;
}

Window::Window(WindowManager *parent, beer::uint width, beer::uint height)
    : _parent(parent), _region({{0, 0}, {width, height}}) {
  _graphics =
      parent == nullptr
          ? nullptr
          : new WindowGraphics(_parent->getGraphics()); // TODO memory leak here
}

bool Window::addComponent(WindowedComponent const &component) {
  if (_parent == nullptr || component.cmp == nullptr)
    return false;
  uint comp = _parent->registerComponent(this, component);
  _components.push_back(comp);
  if (_components.size() == 1) {
    getComponent(0)->cmp->setHover(true);
  }

  return true;
}

void Window::draw() {
  if (_graphics == nullptr || _parent == nullptr)
    return;
  for (uint i = 0; i < _components.size(); i++) {
    WindowedComponent *comp = getComponent(i);
    if (comp->cmp->isVisible()) {
      Region offset_region = comp->cmp->getRegion();
      offset_region.top_left += getComponent(i)->position;
      offset_region.bottom_right += getComponent(i)->position;
      _graphics->setRegion(offset_region);
      comp->cmp->draw(*_graphics);
    }
  }
}

void Window::onEvent(InputEvent const &event) {
  if (_parent == nullptr)
    return;
  if (_cursor_state == CursorState::WINDOW) {
    getComponent(_cursor_pos)->cmp->setHover(false);
    switch (event) {
    case (InputEvent::MINUS):
      if (_cursor_pos == 0) {
        _cursor_pos = _components.size() - 1;
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
      getComponent(_cursor_pos)->cmp->activate();
      if (getComponent(_cursor_pos)->cmp->isActive()) {
        _cursor_state = CursorState::COMPONENT;
      }
      break;
    }

    getComponent(_cursor_pos)->cmp->setHover(true);
  } else {
    getComponent(_cursor_pos)->cmp->handleEvent(event);
    if (!getComponent(_cursor_pos)->cmp->isActive()) {
      _cursor_state = CursorState::WINDOW;
    }
  }
}

void Window::setParent(WindowManager *parent) { _parent = parent; }

beer::uint Window::getWidth() const {
  return _region.bottom_right.x - _region.top_left.x;
}
beer::uint Window::getHeight() const {
  return _region.bottom_right.y - _region.top_left.y;
}

WindowedComponent *Window::getComponent(beer::uint idx) {
  if (_parent == nullptr)
    return nullptr;
  return _parent->componentAt(_components[idx]);
}

// -------------- Window Manager -------------------------

WindowManager::WindowManager(Graphics &g, beer::uint width, beer::uint height)
    : _windows(3), _components(1), _graphics(g), _active_window(-1),
      _width(width), _height(height) {}

WindowManager::~WindowManager() {}

void WindowManager::update() {
  if (_next_window != -1 && _active_window != _next_window) {
    _active_window = _next_window;
    _graphics.clear();
  }
  if (_active_window == -1) {
    // TODO log that no window in focus
    return;
  }
  _windows[_active_window].draw();
  _graphics.update();
}

Window *WindowManager::createWindow() {
  _windows.push_back(Window{this, _width, _height});
  const uint current_idx = _windows.size() - 1;
  if (current_idx == 0) {
    _active_window = current_idx;
    _next_window = _active_window;
  }
  Window *ret = &_windows[current_idx];
  return ret;
}

bool WindowManager::makeActive(beer::uint id) {
  if (id < _windows.size()) {
    _next_window = id;
    return true;
  }
  return false;
}

void WindowManager::onEvent(InputEvent const &event) {
  _windows[_active_window].onEvent(event);
}

Graphics &WindowManager::getGraphics() const { return _graphics; }

beer::uint
WindowManager::registerComponent(Window *win,
                                 WindowedComponent const &component) {
  _components.push_back(component);
  return _components.size() - 1;
}

WindowedComponent *WindowManager::componentAt(uint idx) {
  WindowedComponent *ret = nullptr;
  if (idx < _components.size()) {
    ret = &_components[idx];
  }
  return ret;
}
