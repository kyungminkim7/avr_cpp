cmake_minimum_required(VERSION 3.15)
project(AvrCpp LANGUAGES CXX)

#----------------------------
# Project Settings
#----------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)

find_package(etl REQUIRED CONFIG)

#----------------------------
# Global Options
#----------------------------
set(NUM_USART_MODULES 1 CACHE STRING "Number of USART modules")
set(TIMER_MODULES 0 2 CACHE STRING "Timer module numbers")
set(HIGH_RESOLUTION_TIMER_MODULES 1 CACHE STRING "High resolution timer module numbers")

#----------------------------
# Build
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

# avr_cpp Attributes
target_include_directories(avr_cpp PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)

target_link_libraries(avr_cpp PUBLIC etl::etl)

#----------------------------
# Test (off-board)
#----------------------------
if (NOT BUILD_TESTING STREQUAL OFF)
    add_subdirectory(avr_stub)

    enable_testing()
    add_subdirectory(test)
endif()

#----------------------------
# Install
#----------------------------
include(GNUInstallDirs)

install(TARGETS avr_cpp
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_BINARY_DIR}/include/
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
)
