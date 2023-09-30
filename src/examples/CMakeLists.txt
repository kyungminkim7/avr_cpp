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
    TARGET usart
    MCU "${MCU}"
    PROGRAMMER_TYPE "${PROGRAMMER_TYPE}"
    SOURCES usart.cpp
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARIES avr_cpp
)
