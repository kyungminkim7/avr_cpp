# avr_cpp
This project provides a C++ library (Conan package) for programming AVR microcontrollers.

This has been tested on an Ubuntu 24.04 host system cross-compiling for an Atmega168p target system.

### Dependencies
- Conan package manager
- avrdude
- avr-libc
- binutils-avr
- cmake
- gcc-avr supporting C++17 or higher
- C++ compiler supporting C++17 or higher for compiling on host system and running unit tests

### Creating a Conan package for AVR target systems (run from project root directory)
- Create a Conan profile similar to: `profiles/avr`
- Create the Conan package: `conan create . --profile=avr -o mcu=<MCU>`
- Import the Conan package in your own project as shown in: `examples`
- Flash executables onto AVR: `./flash_avr.sh -p <PROGRAMMER> -m <MCU> <APP>`

### Example - ATMega168 with USBTiny programmer
```bash
conan create . --profile=profiles/avr -o mcu=atmega168

conan build examples/ --profile=profiles/avr

./flash_avr.sh \
    -p usbtiny \
    -m atmega168 \
    examples/build/Release/analog_digital_converter

# View serial output if connected
screen /dev/ttyUSB0 9600
```