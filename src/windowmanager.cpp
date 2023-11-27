#include "windowmanager.h"
#include "window.h"

WindowManager::WindowManager(Graphics& g, beer::uint width, beer::uint height)
    : _windows(nullptr), _graphics(g), _active_window(0) {}

void WindowManager::update() {
    _windows->draw();
    _graphics.update();
}

void WindowManager::add(beer::uint id, Window const& window) {
    if (id != 0) return;
    _windows = new Window(window);
    _windows->setParent(this);
    _nwindows = 1;
    makeActive(0);
}

bool WindowManager::makeActive(beer::uint id) {
    if (_nwindows > 0 && id < _nwindows) {
        _active_window = id;
        return true;
    }
    return false;
}

void WindowManager::onEvent(InputEvent const& event) {
    _windows[0].onEvent(event);
}

Graphics& WindowManager::getGraphics() const {
    return _graphics;
}
