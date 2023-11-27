#include <iostream>
#include <memory>
#include <stdio.h>
#include <signal.h>
#include <assert.h>

#include "BeerGUI.h"
#include "GLBackend.h"
#include "component.h"
#include "core.h"

using namespace beer;
// -----

bool running;

void finish(int sig) {
    running = false;
}

int main(int argc, char *argv[]) {
    running = true;
    signal(SIGINT, finish);

    GLBackend backend(emulator::width, emulator::height);
    Renderer<GLBackend> ren(&backend);

    ren.setup();

    WindowManager manager(ren, emulator::width, emulator::height);
    Window window(emulator::width, emulator::height);

    SliderComponent slider({{10, 10}, {110, 20}}, 255/2);

    assert(window.addComponent(&slider));
    manager.add(0, window);
    slider.draw(ren);
    // ren.fill({{10,10}, {110, 20}}, {255, 255, 255});

    while (running) {
        manager.update();
        std::vector<InputEvent> events = backend.clearEvents();
        for (InputEvent const& event : events) {
            manager.onEvent(event);
        }

        // g.drawPixel(1, 1, 0xffff);
        // ren.update();
    }

    return 0;
}


