#include "component.h"

void Component::setVisible(bool visible) {
    _isVisible = visible;
}


SliderComponent::SliderComponent(uint8_t initial_progress) {

}

void SliderComponent::handleEvent(InputEvent const& event_type) {
    switch(event_type) {
        case(InputEvent::MINUS):
            if (_progress > 0) _progress--;
            break;
        case(InputEvent::PLUS):
            if (_progress < 255) _progress++;
            break;
        case(InputEvent::SELECT):
            break;
    }

}

void SliderComponent::draw(Graphics const& g) {

}
