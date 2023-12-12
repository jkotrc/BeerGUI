#define BEER_LINUX
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <signal.h>

#include "GLBackend.h"
#include "core.h"

#define WIDTH emulator::width
#define HEIGHT emulator::height

/**
 * This file uses BeerGUI to create an example interface
 * on a computer screen. It has been styled to closely
 * resemble an arduino sketch. See the arduino section delineated
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

    ButtonComponent::Action onClick1 = []() { //define button action
        std::cout << "Going to settings\n";
         manager.makeActive(W_SETTINGS); //switch between windows
    };
    ButtonComponent::Action onClick2 = []() {
        std::cout << "Going to main menu\n";
         manager.makeActive(W_MAINMENU);
    };

    windows[W_MAINMENU]->addComponent({{0,10}, new SliderComponent({50, 5}, 30)});
    windows[W_MAINMENU]->addComponent({{0,30}, new ButtonComponent({10, 10}, onClick1)});

    windows[W_SETTINGS]->addComponent({{30,10}, new SliderComponent({50, 5}, 60)});
    windows[W_SETTINGS]->addComponent({{30,20}, new SliderComponent({50, 5}, 255/2)});
    windows[W_SETTINGS]->addComponent({{30,30}, new ButtonComponent({10, 10}, onClick2)});

    manager.makeActive(W_MAINMENU); //switch between windows
    // manager.makeActive(W_SETTINGS);
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
            switch(event) {
                case(InputEvent::MINUS):
                    std::cout << "INPUT: -\n";
                    break;
                case(InputEvent::PLUS):
                    std::cout << "INPUT: +\n";
                    break;
                case(InputEvent::SELECT):
                    std::cout << "INPUT: select\n";
                    break;

            }
            manager.onEvent(event);
        }
    }

    return 0;
}
