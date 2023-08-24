include(GetGoogleTest)

# AVR system library stub
add_subdirectory(avr_stub)
target_link_libraries(avr_cpp PUBLIC avr_stub)

# Testing library
add_library(avr_cpp_test
    matchers.cpp
)

target_include_directories(avr_cpp_test PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)

target_link_libraries(avr_cpp_test PUBLIC 
    avr_cpp
    gtest
    gmock
    gtest_main
)