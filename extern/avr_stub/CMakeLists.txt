# AVR stub library for unit testing on host machine builds
add_library(avr_stub
    io.cpp
)

target_include_directories(avr_stub PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)