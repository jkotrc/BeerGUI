
set(DISPLAYLIB_SOURCES
  core.cpp
  window.cpp
  component.cpp
  slider.cpp
  button.cpp
)

set(DISPLAYLIB_HEADERS
  windowmanager.h
  window.h
  component.h
  slider.h
  renderer.h
)

add_library(displaylib ${DISPLAYLIB_SOURCES})
