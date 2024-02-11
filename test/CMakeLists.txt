find_package(GTest REQUIRED CONFIG)
include(GoogleTest)

add_executable(avr_cpp_test
    src/test_analog_digital_converter.cpp
    src/test_angle.cpp
    src/test_bit.cpp
    src/test_chrono.cpp
    src/test_external_interrupt.cpp
    src/test_math.cpp
    src/test_pin_change_interrupt.cpp
    src/test_port.cpp
    src/test_pulse_width_modulation.cpp
    src/test_ratio.cpp
    src/test_servo.cpp
    src/test_timer.cpp
    src/test_type_traits.cpp
    src/test_usart.cpp
)

target_include_directories(avr_cpp_test PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)

target_link_libraries(avr_cpp_test
    avr_cpp
    GTest::gmock
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(avr_cpp_test)