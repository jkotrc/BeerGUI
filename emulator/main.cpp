#include <iostream>
#include <memory>
#include <stdio.h>
#include <signal.h>

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

    //void setup()
    GLBackend backend(emulator::width, emulator::height);
    Renderer<GLBackend> ren(&backend);
    ren.setup();

    WindowManager manager(ren, emulator::width, emulator::height);
    Window window(emulator::width, emulator::height);

    SliderComponent slider({{10, 10}, {110, 20}}, 255/2);
    SliderComponent slider2({{10, 30}, {110, 40}}, 255/2);
    // ButtonComponent btn({{150, 30}, {150+30, 30+30}}, [](Component* cmp){
    //     printf("Hello from button!\n");
    // });

    window.addComponent(&slider);
    window.addComponent(&slider2);
    manager.add(0, window);

    while (running) {
        //void loop()
        manager.update();
        std::vector<InputEvent> events = backend.clearEvents();
        for (InputEvent const& event : events) {
            manager.onEvent(event);
        }
    }

    return 0;
}


