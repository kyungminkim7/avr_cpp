# AVR system library stub
add_subdirectory(avr_stub)
target_link_libraries(avr_cpp PUBLIC avr_stub)

# Testing library
add_library(avr_cpp_test INTERFACE)

target_include_directories(avr_cpp_test INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

target_link_libraries(avr_cpp_test INTERFACE avr_cpp)