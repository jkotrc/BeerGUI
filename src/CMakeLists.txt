
set(DISPLAYLIB_SOURCES
  core.cpp
  window.cpp
  component.cpp
)

set(DISPLAYLIB_HEADERS
  windowmanager.h
  window.h
  component.h
  renderer.h
)

add_library(displaylib ${DISPLAYLIB_SOURCES})
