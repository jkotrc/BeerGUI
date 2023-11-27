#ifndef WINDOW_H_
#define WINDOW_H_

#include "windowmanager.h"

class Window {
    public:
        Window(unsigned int width, unsigned int height);
        void init();
        void draw();

    private:
        unsigned int _width;
        unsigned int _height;
        WindowManager* _parent;
};


#endif // WINDOW_H_
