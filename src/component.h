#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "core.h"
#include "renderer.h"

class Window;

// constexpr Color active_color = Color{0xaa, 0xaa, 0xff};
constexpr Color active_color = Color{0x00, 0x00, 0x00};

/**
 * Base class for components. Each new component should derive from this
 * and provide code for drawing and handling user input.
 *
 * Cursor is managed by parent window. If the component is selected,
 * `activate()` is called, which must promise to est `_active` to true,
 * which has the effect of capturing input in this component until `_active`
 * becomes false again
 */
class Component {
public:
  virtual ~Component();
  /**
   * Specific components provide their own ways of handling events.
   * Make sure there is a way for the user to exit the component!
   */
  virtual void handleEvent(InputEvent const &event_type) = 0;
  /// Customizable draw method. Should have a visual distinction for when the
  /// component is selected
  virtual void draw(Graphics &graphics) = 0;
  void setVisible(bool visible);
  /// Set hover state. Ensure `draw` makes component look different when
  /// selected with cursor
  void setHover(bool hover);
  /// Called when component selected. Gives control over inputs
  virtual void activate();

  /// Whether the component is hidden
  bool isVisible() const;
  /// Whether the component is in control of inputs
  bool isActive() const;
  beer::uint getWidth() const;
  beer::uint getHeight() const;
  Region getRegion() const;

protected:
  Region _region;
  bool _isVisible = true;
  /// A component is cursorable when the cursor should cycle over this component
  bool _cursorable = false;
  bool _hover = false;
  bool _active = false;
  Window *_parent = nullptr;
};

#endif // COMPONENT_H_
