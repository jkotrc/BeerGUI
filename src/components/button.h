#ifndef BUTTON_H_
#define BUTTON_H_

#include "../component.h"

class ButtonComponent : public Component {
    public:
        using ButtonFunc = void (*)(ButtonComponent* cmp);
        ButtonComponent(Region const& region, ButtonFunc func);
        void handleEvent(InputEvent const& event_type) override;
        void draw(Graphics& graphics) override;
    protected:
        ButtonFunc _action;
        uint8_t _progress;
        bool _cursorable = true;
};

#endif // BUTTON_H_
