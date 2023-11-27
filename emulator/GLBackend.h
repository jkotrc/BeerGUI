#ifndef GLBACKEND_H_
#define GLBACKEND_H_

#define GLEW_STATIC

#include <cstdint>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.h"

/**
 * Use OpenGL and GLFW to create
 * primitive window on PC
 * for the display emulator.
 */
class GLBackend {
    public:
        GLBackend() = default;
        ~GLBackend();
        using BufType = uint8_t;
        /// Call to initialize drawing capabilites
        bool init();
        /// Call in a loop to keep window alive
        void update();
        /// Clear screen
        void clear();

    private:
        // See https://www.glfw.org/docs/latest/window_guide.html#window_object
        GLFWwindow* _window;
};

/*
 * This declaration defines the symbol Renderer<GLBackend>
 * so that the source file can provide its implementation
 */
using GLRenderer = Renderer<GLBackend>;

#endif // GLBACKEND_H_
