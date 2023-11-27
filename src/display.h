#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "renderer.h"
#include "component.h"
#include "windowmanager.h"

template <typename Renderer>
class Display;

template <typename RenderBackend>
class Display<Renderer<RenderBackend>> {
    public:
        using DisplayRenderer = Renderer<RenderBackend>;
        Display(uint8_t width, uint8_t height, DisplayRenderer&& renderer);
        ~Display();

    private:
        DisplayRenderer* _renderer;


};

#endif // DISPLAY_H_
