#include <iostream>
#include <memory>
#include <stdio.h>
#include <signal.h>

#include "GLBackend.h"

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

GLBackend backend(emulator::width, emulator::height);
Renderer<GLBackend> ren(&backend);
WindowManager manager(ren, emulator::width, emulator::height);
Window window(emulator::width, emulator::height);

SliderComponent slider({{10, 10}, {110, 20}}, 255/2);
SliderComponent slider2({{10, 30}, {110, 40}}, 255/2);

void setup() {
    window.addComponent(&slider);
    window.addComponent(&slider2);
    manager.add(0, window);
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
