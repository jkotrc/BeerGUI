# Beer GUI

## Overview

This project provides a small useful toolkit for building simple embedded display interfaces. The `src` folder can be included through the Arduino IDE for use in your sketch. It is expected to work with any display using `Adafruit_GFX`, which BeerGUI depends on.

To get BeerGUI working on any other display, you must have a rendering class (like `Adafruit_GFX`) for the display. Then, a `Renderer<Backend>` class needs to be defined for that rendering class. An instance is fed to `WindowManager`

### Basic Features
- Usable on a wide class of display hardware
- basic window manager with cursor and 3 input control
- Reusable, customizable components

### Planned Featuers
- Unicode display and fonts
- Multiple windows visible on screen
- Overlapping windows
- More general input


## Setup

### Arduino

In the Arduino IDE, go to `Sketch > Include Library > Add .ZIP Library` and select the `src/` folder (it doesn't need to be zip archived). See `examples/` for example arduino sketches

### Linux

BeerGUI can be used as a C++ library. An example project `emulator/` simulates a SSD1306 display interface. To build the library and emulator, run these commands

``` sh
./setup-emulator.sh
make -j<N> #optional argument -j to use more CPU cores for speed. For example -j4
```
If successful, this will create the emulator executable in the `dist/` folder.

### Windows (TBA)

The C++ library and emulator can be built on windows, but will require installing visual studio and probably adding extra configuration in `CMakeLists.txt`. Contributions welcome

## Documentation

See `examples/` folder for usage. More detailed code documentation should be visible within IDEs. Full documentation in HTML format can be generated using `doxygen`. See `docs/html/index.html` for the generated documentation page
