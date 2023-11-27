#include "GLBackend.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <stdio.h>

#define WIDTH 126*2
#define HEIGHT 64*2

GLBackend::~GLBackend() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool GLBackend::init() {
    if (!glfwInit()) {
        throw "Failed to initialize GLFW";
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = glfwCreateWindow(WIDTH, HEIGHT, "Vape Emulator", NULL, NULL);
    printf("Made window: %p\n", _window);
    if(_window == NULL)
    {
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
    glfwSetKeyCallback(_window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            //TODO Call _WindowManager here
            //_Window::_windowPointer->handleKeys(key, scancode, action, mods);
        });

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw "Failed to create GL context";
    }

    glClearColor(0.4f, 0.0f, 1.0f, 0.0f);
    return true;
}

void GLBackend::update() {
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

void GLBackend::clear() {
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(_window);
}

template<>
GLRenderer::Renderer() {
    printf("Creating renderer with GL Backend\n");
    _backend = new GLBackend();
}

template<>
void GLRenderer::setup() {
    bool status;
    try {
        status = _backend->init();
    } catch(std::exception const& e) {
        status = false;
        std::cerr << "Error during backend init: " << e.what() << std::endl;
    }
    if (!status) {
        std::cerr << "Backend init returned false!\n";
    }
}

template<>
void GLRenderer::drawPixel(int16_t x, int16_t y, uint16_t color) {

}

template<>
void GLRenderer::fill(Point const &tl, Point const &br) {

}

template<>
void GLRenderer::update() {
    printf("Renderer loop\n");
    _backend->update();
}

template<>
void GLRenderer::clear() {

}
