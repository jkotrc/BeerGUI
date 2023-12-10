#ifndef RENDERER_H_
#define RENDERER_H_

#include "core.h"

/**
 * Base class for all drawing. Components use this to draw themselves
 */
class Graphics {
  public:
    /// set pixel color at given point
    virtual void drawPixel(Point const& point, Color const& color) = 0;
    /// fill region with given color
    virtual void fill(Region const& region, Color const& color) = 0;
    /// draw colored line between points
    virtual void drawLine(Point const& from, Point const& to, Color const& color) = 0;
    /// must be called once per loop to update display
    virtual void update() = 0;
    //TODO
    //void drawBitmap
    virtual void drawText(Point const& anchor, const char* text, Color const& color) = 0;
};

/**
 * TODO: Renderer semantics "hardware render library" GLBackend -> GLRenderLib, Adafruit_GFX
 * This is the base interface that display code uses to draw components.
 * It can be customized with a given RenderBackend class to adapt its use
 * to different displays / contexts. Currently, two variants will be used:
 *
 * - `Renderer<GLBackend>`        draws to a PC screen, used by emulator
 * - `Renderer<Adafruit_GFX>`     draws to GFX display using the arduino library
 *
 * ## How to customize
 *
 * To get the GUI working for a different display that depends on a different hardware library,
 * you will need to wrap the dependency in a class. With most Adafruit displays, this is already
 * done through the Adafruit_GFX library. Otherwise (1) create a class to interface with the
 * hardware library analogous to GLBackend and (2) write a specialization for Renderer.
 *
 * Once finished with (1), declare this in your custom backend's header file `myrenderlib.h`
 *
 * ``template <> using MyRenderer = Renderer<MyRenderLib>``
 *
 * then define all the functions from the interface in the sources `myrenderlib.cpp`,
 * for example
 *
 * ``template <> void MyRenderer::setup() { ... }``
 *
 */
template <typename RenderBackend>
class Renderer : public Graphics {
  public:
    Renderer(RenderBackend* backend) {
        _backend = backend;
    }
    Renderer() : Renderer(new RenderBackend()) {}
    void clear();
    void setup();

    void update() override;
    void drawPixel(Point const& point, Color const& color) override;
    void fill(Region const& region, Color const& color) override;
    void drawLine(Point const& from, Point const& to, Color const& color) override;
    void drawText(Point const& anchor, const char* text, Color const& color) override;
  private:
    RenderBackend* _backend;
};


#endif // RENDERER_H_
