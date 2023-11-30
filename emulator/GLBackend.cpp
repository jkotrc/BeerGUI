#include "GLBackend.h"
#include "GLFW/glfw3.h"
#include "core.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace beer;

GLuint compileShader(std::string vertexSource, std::string fragmentSource);

constexpr const char *VERT_SHADER = R"(
#version 330 core

layout(location = 0) in vec2 vertexPosition; // Vertex position input
out vec2 texCoord; // Texture coordinate output

void main() {
    // Set the vertex position
    gl_Position = vec4(vertexPosition, 0.0, 1.0);

    // Calculate texture coordinates (assuming texture covers [0, 1] in both dimensions)
    texCoord = vertexPosition * 0.5 + 0.5;
})";

constexpr const char *FRAG_SHADER = R"(
#version 330 core

in vec2 texCoord; // Texture coordinate input
uniform sampler2D textureSampler; // Texture sampler uniform

out vec4 fragColor; // Fragment color output

void main() {
    // Sample the texture using the provided texture coordinates
    vec4 texColor = texture(textureSampler, texCoord);

    // Output the sampled color as the final fragment color
    fragColor = texColor;
}
)";

GLBackend::GLBackend(uint width, uint height)
    : _dims{width, height}, _window(nullptr) {
  uint32_t *buf = new uint32_t[width * height];
  for (uint i = 0; i < width*height; i++) {
      buf[i] = 0xcccc00;
      // if (i % 2 == 0) {
      //   buf[i] = 0xff00ff;
      // } else {
      //   buf[i] = 0x00ffff;
      // }
      // printf("Buf[%u] = %x\n", i, buf[i]);
  }
  _screen = {buf, width, height};
}

GLBackend::~GLBackend() {
  glfwDestroyWindow(_window);
  glfwTerminate();
  delete _screen.buf;
}

bool GLBackend::init() {
  if (!glfwInit()) {
    throw "Failed to initialize GLFW";
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  _window = glfwCreateWindow(emulator::width, emulator::height, "Vape Emulator",
                             NULL, NULL);
  printf("Made window: %p\n", _window);
  if (_window == NULL) {
    glfwTerminate();
    throw "Failed to create GLFW window";
  }

  glfwMakeContextCurrent(_window);
  // glfwSetFramebufferSizeCallback(_window,
  //     [](GLFW_window *_window, int width, int height)
  //     {
  //         glViewport(0, 0, width, height);
  //         ResourceManager::ViewportWidth = width;
  //         ResourceManager::ViewportHeight = height;
  //         _Window::_windowPointer->resize();
  //     });
  glfwSetWindowUserPointer(_window, this);
  glfwSetKeyCallback(_window, [](GLFWwindow *window, int key, int scancode,
                                 int action, int mods) {
    GLBackend *ptr = (GLBackend *)glfwGetWindowUserPointer(window);
    // TODO Call _WindowManager here
    //_Window::_windowPointer->handleKeys(key, scancode, action, mods);
    if (action != GLFW_PRESS) return;
    switch (key) {
    case (GLFW_KEY_A):
      ptr->onEvent(InputEvent::MINUS);
      break;
    case (GLFW_KEY_S):
      ptr->onEvent(InputEvent::SELECT);
      break;
    case (GLFW_KEY_D):
      ptr->onEvent(InputEvent::PLUS);
      break;
    default:
      break;
    }
  });

  if (glewInit() != GLEW_OK) {
    glfwTerminate();
    throw "Failed to create GL context";
  }

  GLuint vao, vbo;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);

  _shader = compileShader(VERT_SHADER, FRAG_SHADER);

  const GLfloat quadVertices[] = {
      -1.0f, -1.0f,
      1.0f, -1.0f,
      -1.0f, 1.0f,
      1.0f, 1.0f,
  };

  glClearColor(0.4f, 0.8f, 0.3f, 0.5f);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices,
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
                        (GLvoid *)0);

  glGenTextures(1, &_textureID);
  glBindTexture(GL_TEXTURE_2D, _textureID);

  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               _dims.x,
               _dims.y,
               0,
               GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,
               _screen.buf);

  glUseProgram(_shader);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  return true;
}

uint step = 0;
void GLBackend::update() {
  glBindTexture(GL_TEXTURE_2D, _textureID);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               _dims.x,
               _dims.y,
               0,
               GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,
               _screen.buf);

  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(_shader);
  glUniform1i(glGetUniformLocation(_shader, "textureSampler"), 0);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glfwSwapBuffers(_window);
  glfwPollEvents();
}

void GLBackend::clear() {
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(_window);
}

void GLBackend::onEvent(InputEvent const &event_type) {
  _eventQueue.push_back(event_type);
}

std::vector<InputEvent> GLBackend::clearEvents() {
  std::vector<InputEvent> ret = _eventQueue;
  _eventQueue.clear();
  return ret;
}

// template<>
// GLRenderer::Renderer() {
//     printf("Creating renderer with GL Backend\n");
//     _backend = new GLBackend();
// }

template <> void GLRenderer::setup() {
  bool status;
  try {
    status = _backend->init();
  } catch (std::exception const &e) {
    status = false;
    std::cerr << "Error during backend init: " << e.what() << std::endl;
  }
  if (!status) {
    std::cerr << "Backend init returned false!\n";
  }
}

uint32_t getPixelColor(Color const& color) {
    uint32_t ret = (color.b << 8) | (color.g << 16) | (color.r << 24);
    return ret;
}

template <>
void GLRenderer::drawPixel(Point const &point, Color const &color) {
    if(point.x <=_backend->_dims.x && point.y <= _backend->_dims.y) {
        *_backend->_screen.at(point) = getPixelColor(color);
    }
}

template <> void GLRenderer::fill(Region const &region, Color const &color) {
    for (uint i = region.top_left.x; i < region.bottom_right.x; i++) {
      for (uint j = region.top_left.y; j < region.bottom_right.y; j++) {
          // *_backend->_screen.at({i, _backend->_dims.y-j}) = 0xff000000;
          *_backend->_screen.at({i, _backend->_dims.y-j}) = getPixelColor(color);
      }
    }
}

template <>
void GLRenderer::drawLine(Point const &from, Point const &to,
                          Color const &color) {}

template <> void GLRenderer::update() {
  _backend->update();
}

template <> void GLRenderer::clear() {}

GLuint compileShader(std::string vertexSource, std::string fragmentSource) {
  // Read our shaders into the appropriate buffers

  // Create an empty vertex shader handle
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // Send the vertex shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  const GLchar *source = (const GLchar *)vertexSource.c_str();
  glShaderSource(vertexShader, 1, &source, 0);

  // Compile the vertex shader
  glCompileShader(vertexShader);

  GLint isCompiled = 0;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

    // We don't need the shader anymore.
    glDeleteShader(vertexShader);

    // Use the infoLog as you see fit.

    // In this simple program, we'll just leave
    throw "Failed to compile!";
  }

  // Create an empty fragment shader handle
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Send the fragment shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  source = (const GLchar *)fragmentSource.c_str();
  glShaderSource(fragmentShader, 1, &source, 0);

  // Compile the fragment shader
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

    // We don't need the shader anymore.
    glDeleteShader(fragmentShader);
    // Either of them. Don't leak shaders.
    glDeleteShader(vertexShader);

    // Use the infoLog as you see fit.

    // In this simple program, we'll just leave
    throw "Failed to compile!";
  }

  // Vertex and fragment shaders are successfully compiled.
  // Now time to link them together into a program.
  // Get a program object.
  GLuint program = glCreateProgram();

  // Attach our shaders to our program
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  // Link our program
  glLinkProgram(program);

  // Note the different functions here: glGetProgram* instead of glGetShader*.
  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    // We don't need the program anymore.
    glDeleteProgram(program);
    // Don't leak shaders either.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Use the infoLog as you see fit.

    // In this simple program, we'll just leave
    throw "Failed to compile!";
  }

  // Always detach shaders after a successful link.
  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);

  return program;
}
