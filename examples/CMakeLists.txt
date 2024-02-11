cmake_minimum_required(VERSION 3.15)
project(avr_cpp_examples CXX)

set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)

find_package(avr_cpp CONFIG REQUIRED)
link_libraries(avr_cpp::avr_cpp)

add_executable(analog_digital_converter src/analog_digital_converter.cpp)
add_executable(elapsed_time src/elapsed_time.cpp)
add_executable(external_interrupt src/external_interrupt.cpp)
add_executable(pin_change_interrupt src/pin_change_interrupt.cpp)
add_executable(pulse_width_modulation src/pulse_width_modulation.cpp)
add_executable(servo_characterization src/servo_characterization.cpp)
add_executable(servo src/servo.cpp)
add_executable(timer src/timer.cpp)
add_executable(usart src/usart.cpp)