#ifndef RENDERER-FAKE_H_
#define RENDERER-FAKE_H_

#include <core.h>
#include <renderer.h>

class FakeRenderer {
    public:
        FakeRenderer() = default;
};

using FRenderer = Renderer<FakeRenderer>;

template<>
void FRenderer::clear() {}

template<>
void FRenderer::update() {}

template<>
void FRenderer::drawPixel(Point const& point, Color const& color) {}

template<>
void FRenderer::fill(Region const& region, Color const& color) {}

template<>
void FRenderer::drawLine(Point const& from, Point const& to, Color const& color) {}

template<>
void FRenderer::drawText(Point const& anchor, const char* text, Color const& color) {}

#endif // RENDERER-FAKE_H_
