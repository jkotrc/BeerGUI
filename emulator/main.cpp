#include <cstdint>
#include <iostream>
#include <memory>
#include <cassert>
#include <stdio.h>
#include <signal.h>

#include "GLBackend.h"

#define WIDTH emulator::width
#define HEIGHT emulator::height

/**
 * This file uses BeerGUI to create an example interface
 * on a computer screen. It has been styled to closely
 * resemble use on arduino. See the arduino section delineated
 * by comments for the "sketch" part.
 *
 */

//START of Arduino

#include "BeerGUI.h" //Use angle brackets <BeerGUI.h> in arduino
using namespace beer;

enum Windows {
    W_MAINMENU = 0,
    W_SETTINGS,
    W_NWINDOWS
};

GLBackend backend(WIDTH, HEIGHT);
Renderer<GLBackend> ren(&backend);
WindowManager manager(ren, WIDTH, HEIGHT);
Window* windows[W_NWINDOWS];

void setup() {
    windows[W_MAINMENU] = manager.add();
    windows[W_SETTINGS] = manager.add();
    // manager.addComponent(windows[W_MAINMENU], {{10,10}, new ButtonComponent("Settings", manager.transition(W_SETTINGS))});
    assert(windows[W_MAINMENU]->addComponent({{10,10}, new SliderComponent({50, 5}, 255/2)}));
    assert(windows[W_MAINMENU]->addComponent({{30,50}, new SliderComponent({50, 5}, 255/2)}));
    // manager.addComponent(windows[W_SETTINGS], {{WIDTH/2,HEIGHT/2}, new ButtonComponent("Back", manager.transition(W_MAINMENU))});
}

void loop() {
    manager.update();
}

//END of arduino

bool running;

void finish(int sig) {
    running = false;
}

int main(int argc, char *argv[]) {
    running = true;
    signal(SIGINT, finish);

    setup();

    while (running) {
        //void loop()
        loop();
        std::vector<InputEvent> events = backend.clearEvents();
        for (InputEvent const& event : events) {
            manager.onEvent(event);
        }
    }

    return 0;
}
