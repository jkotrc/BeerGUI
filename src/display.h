#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "renderer.h"
#include "component.h"
#include "windowmanager.h"

template <typename Renderer>
class Display;

template <typename RenderBackend>
class Display<Renderer<RenderBackend>> {


};

#endif // DISPLAY_H_
