#!/usr/bin/env sh

mkdir -p build
cd build

cmake -DBEER_BUILD_EMULATOR=1 -DBEER_BUILD_TESTS=1 ..
# cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/Arduino-toolchain.cmake .. \
#     -DCMAKE_C_COMPILER=/home/john/.arduino15/packages/esp32/tools/xtensa-esp32-elf-gcc/esp-2021r2-patch5-8.4.0/bin/xtensa-esp32-elf-gcc \
#     -DCMAKE_CXX_COMPILER=/home/john/.arduino15/packages/esp32/tools/xtensa-esp32-elf-gcc/esp-2021r2-patch5-8.4.0/bin/xtensa-esp32-elf-g++
