# avr_cpp
This project provides utility libraries and a CMake project template for programming and cross-compiling for AVR microcontrollers using modern C++(14).

This has been tested on an Ubuntu 22.04.1 LTS host system cross-compiling for an Atmega168p target system.

### Dependencies
- avrdude
- avr-libc
- binutils-avr
- cmake
- gcc-avr supporting C++14 or higher
- (Optional) C++ compiler supporting C++17 or higher for compiling on host system and running unit tests

### Build and run unit tests (run from project root directory)
1. `cmake -B build -S .`
2. `cd build`
3. `cmake --build .`
4. `ctest --stop-on-failure -VV`

### Build and flash an AVR app (run from project root directory)
1. Add a project subdirectory following the examples shown in `src/examples`
2. `cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/avr-gcc.cmake`
3. `cmake --build build/ -t <TARGET>`
