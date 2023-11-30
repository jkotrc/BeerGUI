cmake_minimum_required(VERSION 3.10)

project(display_ino CXX)

include_directories(${PROJECT_SOURCE_DIR}/src)


if (NOT DEFINED DISPLAY_BUILD_EMULATOR)
 message("Building with arduino toolchain not yet supported")
 #set(CMAKE_TOOLCHAIN_FILE ${PROJECT_SOURCE_DIR}/cmake/Arduino-toolchain.cmake) # Arduino Toolchain
endif()
message(${CMAKE_SYSTEM_NAME})


SET (CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/dist)

add_subdirectory(fontgen)
add_subdirectory(src)

if (DISPLAY_BUILD_EMULATOR)
    add_definitions(-g -O2 -std=c++17 -Wall -Wextra)
    add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw)
    add_subdirectory(emulator)
else()
    set(DISPLAY_SOURCES
      main.ino
    )
    set(DISPLAY_HEADERS

    )
    add_executable(display ${DISPLAY_SOURCES})
    target_link_arduino_libraries(display PRIVATE core)
    target_link_arduino_libraries(display PRIVATE displaylib)
    target_enable_arduino_upload(display)
    set_target_upload_port(display COM3)
endif()
