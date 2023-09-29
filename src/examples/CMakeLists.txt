include(AVR)

AddExecutableAVR(
    TARGET external_interrupt
    MCU "${MCU}"
    PROGRAMMER_TYPE "${PROGRAMMER_TYPE}"
    SOURCES external_interrupt.cpp
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARIES avr_cpp
)
