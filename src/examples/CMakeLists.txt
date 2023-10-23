include(AVR)

AddExecutableAVR(
    TARGET analog_digital_converter
    MCU "${MCU}"
    PROGRAMMER_TYPE "${PROGRAMMER_TYPE}"
    SOURCES analog_digital_converter.cpp
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARIES avr_cpp
)

AddExecutableAVR(
    TARGET elapsed_time
    MCU "${MCU}"
    PROGRAMMER_TYPE "${PROGRAMMER_TYPE}"
    SOURCES elapsed_time.cpp
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARIES avr_cpp
)

AddExecutableAVR(
    TARGET external_interrupt
    MCU "${MCU}"
    PROGRAMMER_TYPE "${PROGRAMMER_TYPE}"
    SOURCES external_interrupt.cpp
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARIES avr_cpp
)

AddExecutableAVR(
    TARGET pin_change_interrupt
    MCU "${MCU}"
    PROGRAMMER_TYPE "${PROGRAMMER_TYPE}"
    SOURCES pin_change_interrupt.cpp
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARIES avr_cpp
)

AddExecutableAVR(
    TARGET pulse_width_modulation
    MCU "${MCU}"
    PROGRAMMER_TYPE "${PROGRAMMER_TYPE}"
    SOURCES pulse_width_modulation.cpp
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARIES avr_cpp
)

AddExecutableAVR(
    TARGET servo
    MCU "${MCU}"
    PROGRAMMER_TYPE "${PROGRAMMER_TYPE}"
    SOURCES servo.cpp
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARIES avr_cpp
)

AddExecutableAVR(
    TARGET servo_characterization
    MCU "${MCU}"
    PROGRAMMER_TYPE "${PROGRAMMER_TYPE}"
    SOURCES servo_characterization.cpp
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARIES avr_cpp
)

AddExecutableAVR(
    TARGET timer
    MCU "${MCU}"
    PROGRAMMER_TYPE "${PROGRAMMER_TYPE}"
    SOURCES timer.cpp
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARIES avr_cpp
)

AddExecutableAVR(
    TARGET usart
    MCU "${MCU}"
    PROGRAMMER_TYPE "${PROGRAMMER_TYPE}"
    SOURCES usart.cpp
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARIES avr_cpp
)
