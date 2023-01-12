# avr_cpp
This project provides utility libraries and a CMake project template for programming and cross-compiling for AVR microcontrollers.

This has been tested on an Ubuntu 22.04.1 LTS host system cross-compiling for an Atmega168p target system.

### Dependencies
- avrdude
- avr-libc
- binutils-avr
- cmake
- gcc-avr

### Build and flash AVR (from project root directory)
1. `cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/avr-gcc.cmake`
2. `cmake --build build/ -t <TARGET>`
