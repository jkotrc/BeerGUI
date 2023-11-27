#include <iostream>
#include <memory>
#include <stdio.h>
#include <signal.h>

#include "GLBackend.h"

// -----

bool running;

void finish(int sig) {
    running = false;
}




int main(int argc, char *argv[]) {
    running = true;
    signal(SIGINT, finish);

    Renderer<GLBackend> ren;
    Graphics& g = ren;

    ren.setup();

    while (running) {
        g.drawPixel(1, 1, 0xffff);
        ren.update();
    }

    return 0;
}


