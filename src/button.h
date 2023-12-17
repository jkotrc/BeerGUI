#ifndef BUTTON_H_
#define BUTTON_H_

#include "component.h"

/**
 * A rectangular button with configurable on-click action
 */
class ButtonComponent : public Component {
public:
  /// An action is a void function with no return value
  using Action = void (*)();

  /**
   * Create button component with given dimensions and action
   */
  ButtonComponent(Point const &dimensions, Action func);
  void handleEvent(InputEvent const &event_type) override;
  void draw(Graphics &graphics) override;
  void activate() override;

protected:
  Action _action;
  bool _cursorable = true;
};

#endif // BUTTON_H_
