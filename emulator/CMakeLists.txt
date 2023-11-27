# find_package(GLEW REQUIRED)

# include_directories(${GLEW_INCLUDE_DIRS})
# link_libraries(${GLEW_LIBRARIES})

#Which one?
message("Using ${PROJECT_ROOT}/src in includes")
# include_directories(${PROJECT_SOURCE_DIR}/src)

set(EMULATOR_SOURCES
  main.cpp
  GLBackend.cpp
)

set(EMULATOR_HEADERS
  GLBackend.h
)

add_executable(emulator ${EMULATOR_SOURCES})
target_link_libraries(emulator displaylib glfw GLEW GL)
