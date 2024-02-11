# avr_cpp
This project provides a C++ library (Conan package) for programming AVR microcontrollers.

This has been tested on an Ubuntu 22.04.1 LTS host system cross-compiling for an Atmega168p target system.

### Dependencies
- Conan package manager
- avrdude
- avr-libc
- binutils-avr
- cmake
- gcc-avr supporting C++14 or higher
- (Optional) C++ compiler supporting C++17 or higher for compiling on host system and running unit tests

### Creating a Conan package for AVR target systems (run from project root directory)
- Create a Conan profile similar to: `profiles/avr`
- Create the Conan package: `conan create . --profile=avr -o mcu=<MCU>`
- Import the Conan package in your own project as shown in: `examples`
- Flash executables onto AVR: `./flash_avr.sh -p <PROGRAMMER> -m <MCU> <APP>`