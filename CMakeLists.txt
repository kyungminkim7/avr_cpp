cmake_minimum_required(VERSION 3.20)
project(AvrCpp VERSION 1.0.0 LANGUAGES CXX)

#----------------------------
# Project Settings
#----------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/module")
include(GetETL)

enable_testing()

#----------------------------
# Global Options
#----------------------------
set(MCU atmega168 CACHE STRING "Atmel microcontroller type")
set(CPU_FREQ 1000000UL CACHE STRING "Clock frequency")
set(NUM_USART_MODULES 1 CACHE STRING "Number of USART modules")
set(TIMER_MODULES 0 2 CACHE STRING "Timer module numbers")
set(HIGH_RESOLUTION_TIMER_MODULES 1 CACHE STRING "High resolution timer module numbers")

set(PROGRAMMER_TYPE usbtiny CACHE STRING "Programmer type")

#----------------------------
# Library Build
#----------------------------
add_library(avr_cpp
    src/analog_digital_converter.cpp
    src/abstract.cpp
    src/external_interrupt.cpp
    src/interrupt.cpp
    src/memory.cpp
)

# Generate USART source/header files
MATH(EXPR USART_END "${NUM_USART_MODULES}-1")
foreach(n RANGE ${USART_END})
    configure_file(src/usartn.h.in "include/avr_cpp/usart${n}.h")
    configure_file(src/usartn.cpp.in "src/usart${n}.cpp")
    target_sources(avr_cpp PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/src/usart${n}.cpp")
    string(APPEND include_usart_n_headers "\n#include \"usart${n}.h\"")
endforeach()
configure_file(src/usart.h.in "include/avr_cpp/usart.h")

# Generate timer & pulse width modulation source/header files
foreach(n ${TIMER_MODULES})
    # Pulse width modulation
    configure_file(src/pulse_width_modulationn.h.in 
                   "include/avr_cpp/pulse_width_modulation${n}.h")
    configure_file(src/pulse_width_modulationn.cpp.in 
                   "src/pulse_width_modulation${n}.cpp")
    target_sources(avr_cpp PRIVATE 
                   "${CMAKE_CURRENT_BINARY_DIR}/src/pulse_width_modulation${n}.cpp")
    string(APPEND include_pulse_width_modulation_n_headers 
           "\n#include \"pulse_width_modulation${n}.h\"")
endforeach()
configure_file(src/pulse_width_modulation.h.in 
               "include/avr_cpp/pulse_width_modulation.h")

# Generate high resolution timer, pulse width modulation, & servo source/header files
foreach(n ${HIGH_RESOLUTION_TIMER_MODULES})
    # Timer
    configure_file(src/high_resolution_timern.h.in 
                   "include/avr_cpp/high_resolution_timer${n}.h")
    configure_file(src/high_resolution_timern.cpp.in 
                   "src/high_resolution_timer${n}.cpp")
    target_sources(avr_cpp PRIVATE 
                   "${CMAKE_CURRENT_BINARY_DIR}/src/high_resolution_timer${n}.cpp")
    string(APPEND include_high_resolution_timer_n_headers 
           "\n#include \"high_resolution_timer${n}.h\"")

    # Servo
    configure_file(src/servon.h.in 
                   "include/avr_cpp/servo${n}.h")
    configure_file(src/servon.cpp.in 
                   "src/servo${n}.cpp")
    target_sources(avr_cpp PRIVATE 
                   "${CMAKE_CURRENT_BINARY_DIR}/src/servo${n}.cpp")
    string(APPEND include_servo_n_headers 
           "\n#include \"servo${n}.h\"")
endforeach()
configure_file(src/timer.h.in "include/avr_cpp/timer.h")
configure_file(src/servo.h.in "include/avr_cpp/servo.h")

# Define avr_cpp target attributes
target_include_directories(avr_cpp PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)

target_link_libraries(avr_cpp PUBLIC etl::etl)

target_compile_definitions(avr_cpp PUBLIC
    "F_CPU=${CPU_FREQ}"
)

target_compile_options(avr_cpp 
    PUBLIC
        "-fdata-sections"
        "-ffunction-sections"
        "-fno-exceptions"
        "-fno-threadsafe-statics"
        "-Wall"
        "-Wextra"
        "-Wpedantic"
    PRIVATE
        "-Werror"
)

if (CMAKE_SYSTEM_NAME STREQUAL "Generic")
    # AVR build options
    target_compile_options(avr_cpp PUBLIC "-mmcu=${MCU}")

    target_compile_definitions(etl INTERFACE 
        "ETL_NO_STL"
        "ETL_NO_CPP_NAN_SUPPORT"
    )

    target_link_options(avr_cpp PUBLIC
        "-flto"
        "-fuse-linker-plugin"
        "-Wl,--gc-sections"
        "-mmcu=atmega168"
    )

    add_subdirectory(examples)
else()
    # Enable unit tests for host machine builds
    add_subdirectory(test)
endif()