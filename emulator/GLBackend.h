#ifndef GLBACKEND_H_
#define GLBACKEND_H_

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <vector>

#include "core.h"
#include "renderer.h"

namespace emulator {
// Dimensions of the SSD1306 display
constexpr beer::uint width = 128;
constexpr beer::uint height = 64;
} // namespace emulator

/**
 * Use OpenGL and GLFW to create
 * primitive window on PC
 * for the display emulator.
 */

struct Screen {
  uint32_t *buf;
  beer::uint width;
  beer::uint height;
  constexpr uint32_t *at(Point const &p) { return &buf[p.y * width + p.x]; }
};

class GLBackend {
public:
  GLBackend(beer::uint width, beer::uint height);
  ~GLBackend();
  using BufType = uint8_t;
  /// Call to initialize drawing capabilites
  bool init();
  /// Call in a loop to keep window alive
  void update();
  /// Clear screen
  void clear();

  void onEvent(InputEvent const &event_type);
  std::vector<InputEvent> clearEvents();
  Screen _screen;
  ScreenDim _dims;

private:
  std::vector<InputEvent> _eventQueue;
  // See https://www.glfw.org/docs/latest/window_guide.html#window_object
  GLFWwindow *_window;
  GLuint _textureID;
  GLuint _shader;
};

/*
 * This declaration defines the symbol Renderer<GLBackend>
 * so that the source file can provide its implementation
 */
using GLRenderer = Renderer<GLBackend>;

#endif // GLBACKEND_H_
