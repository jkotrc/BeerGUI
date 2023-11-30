
set(DISPLAYLIB_SOURCES
  core.cpp
  window.cpp
  component.cpp
  components/slider.cpp
  components/button.cpp
  windowmanager.cpp
)

set(DISPLAYLIB_HEADERS
  windowmanager.h
  window.h
  component.h
  components/button.h
  renderer.h
)

add_library(displaylib ${DISPLAYLIB_SOURCES})
