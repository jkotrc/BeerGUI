# Beer GUI

This project provides a small useful toolkit for building simple embedded display interfaces. It should be quick to adapt to any specific display and build as an arduino library for your sketch.

Features (Most TBA):
- Quick adaptibility to display libraries
- basic window manager with cursor and state transitiion on input
- Reusable, extendable components
- Unicode display and fonts

A component can be made by making a subclass of `Component`. You can specify the `handleEvent` function and `draw` using drawing primitives
- Text
- Pixel Fill
- Pixel Set
- Bitmap
- Line
- Anything else?

The draw functions of components use the `Graphics` API. The particular implementation is given by the `Renderer` types, depending on which rendering backend you choose (Adafruit, linux OpenGL, ...). 

Arduino seems to automate all the build configuration, but it would nonetheless be useful to have a solid one for this project eventually. This would allow writing embedded code independent of Arduino as well

## Setup

### Arduino (WIP)

It should be possible to add a project description file to the `src/` and then import it into Arduino IDE. 

### Linux

The meat of the project is platform independent and development uses a fake "emulator" to draw the interface in a window and take input from keyboard. To build the emulator, run these commands

``` sh
./setup-emulator.sh
make -j<N> #optional argument -j to use more CPU cores for speed. For example -j4
```
If successful, this will create the emulator executable in the `dist/` folder.

### Windows (TBA)

CMake does exist on windows, but will require installing visual studio and probably some extra configuration in the project's `CMakeLists.txt`. Contributions welcome

## Documentation

See `docs/html/index.html` for the documentation page, but here is a general overview:

