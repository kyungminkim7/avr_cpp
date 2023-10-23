include(GetETL)

add_library(avr_cpp
    analog_digital_converter.cpp
    abstract.cpp
    external_interrupt.cpp
    interrupt.cpp
    memory.cpp
)

# Generate USART source/header files
MATH(EXPR USART_END "${NUM_USART_MODULES}-1")
foreach(n RANGE ${USART_END})
    configure_file(usartn.h.in "include/avr_cpp/usart${n}.h")
    configure_file(usartn.cpp.in "usart${n}.cpp")
    target_sources(avr_cpp PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/usart${n}.cpp")
    string(APPEND include_usart_n_headers "\n#include \"usart${n}.h\"")
endforeach()
configure_file(usart.h.in "include/avr_cpp/usart.h")

# Generate timer & pulse width modulation source/header files
foreach(n ${TIMER_MODULES})
    # Pulse width modulation
    configure_file(pulse_width_modulationn.h.in 
                   "include/avr_cpp/pulse_width_modulation${n}.h")
    configure_file(pulse_width_modulationn.cpp.in 
                   "pulse_width_modulation${n}.cpp")
    target_sources(avr_cpp PRIVATE 
                   "${CMAKE_CURRENT_BINARY_DIR}/pulse_width_modulation${n}.cpp")
    string(APPEND include_pulse_width_modulation_n_headers 
           "\n#include \"pulse_width_modulation${n}.h\"")
endforeach()
configure_file(pulse_width_modulation.h.in 
               "include/avr_cpp/pulse_width_modulation.h")

# Generate high resolution timer, pulse width modulation, & servo source/header files
foreach(n ${HIGH_RESOLUTION_TIMER_MODULES})
    # Timer
    configure_file(high_resolution_timern.h.in 
                   "include/avr_cpp/high_resolution_timer${n}.h")
    configure_file(high_resolution_timern.cpp.in 
                   "high_resolution_timer${n}.cpp")
    target_sources(avr_cpp PRIVATE 
                   "${CMAKE_CURRENT_BINARY_DIR}/high_resolution_timer${n}.cpp")
    string(APPEND include_high_resolution_timer_n_headers 
           "\n#include \"high_resolution_timer${n}.h\"")

    # Servo
    configure_file(servon.h.in 
                   "include/avr_cpp/servo${n}.h")
    configure_file(servon.cpp.in 
                   "servo${n}.cpp")
    target_sources(avr_cpp PRIVATE 
                   "${CMAKE_CURRENT_BINARY_DIR}/servo${n}.cpp")
    string(APPEND include_servo_n_headers 
           "\n#include \"servo${n}.h\"")
endforeach()
configure_file(timer.h.in "include/avr_cpp/timer.h")
configure_file(servo.h.in "include/avr_cpp/servo.h")

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
else()
    # Enable unit tests for host machine builds
    add_subdirectory(test)
endif()