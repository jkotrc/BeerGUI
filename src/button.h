#ifndef BUTTON_H_
#define BUTTON_H_

#include "component.h"

class ButtonComponent : public Component {
    public:
        using Action = void (*)();
        ButtonComponent(Point const& dimensions, Action func);
        void handleEvent(InputEvent const& event_type) override;
        void draw(Graphics& graphics) override;
        void activate() override;
    protected:
        Action _action;
        bool _cursorable = true;
};

#endif // BUTTON_H_
