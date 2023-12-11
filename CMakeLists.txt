cmake_minimum_required(VERSION 3.10)

project(display_ino CXX)

if (BEER_BUILD_TESTS)
 find_package(GTest REQUIRED)
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

include_directories(${PROJECT_SOURCE_DIR}/src)

SET (CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/dist)

#add_subdirectory(fontgen)
add_subdirectory(src)

if (BEER_BUILD_EMULATOR)
    #add_definitions(-g -O2 -std=c++17 -Wall -Wextra)
    add_definitions(-g -std=c++17 -Wall -Wextra)
    #add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw)
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

if (BEER_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    include(GoogleTest)
    add_subdirectory(test)
endif()
