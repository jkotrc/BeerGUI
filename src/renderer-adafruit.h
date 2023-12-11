#ifndef RENDERER-ADAFRUIT_H_
#define RENDERER-ADAFRUIT_H_

#include "core.h"
#include <Adafruit_GFX.h>

/**
 * Renderer implementation using adafruit gfx.
 * Text size 2 is 10x16 pixels
 */
using GFXRenderer = Renderer<Adafruit_GFX>;

const uint16_t clear_color = 0x0000;

template<>
void GFXRenderer::clear() {
    _backend->fillScreen(clear_color);
}

template<>
void GFXRenderer::setup() {

}

template<>
void GFXRenderer::update() {

}

template<>
void GFXRenderer::drawPixel(Point const& point, Color const& color) {
    _backend->drawPixel(point.x, point.y, colorToInt565(color));
}

template<>
void GFXRenderer::fill(Region const& region, Color const& color) {
    const int16_t width = region.bottom_right.x - region.top_left.x;
    const int16_t height = region.bottom_right.y - region.top_left.y;
    _backend->fillRect((int16_t)region.top_left.x, (int16_t)region.top_left.y, width, height, colorToInt565(color));
}

template<>
void GFXRenderer::drawLine(Point const& from, Point const& to, Color const& color) {
    _backend->drawLine(from.x, from.y, to.x, to.y, colorToInt565(color));

}

template<>
void GFXRenderer::drawText(Point const& anchor, const char* text, Color const& color) {
    _backend->setCursor(anchor.x, anchor.y);
    _backend->setTextColor(colorToInt565(color));
    _backend->setTextSize(2);
    _backend->print(text);
}

#endif // RENDERER-ADAFRUIT_H_
