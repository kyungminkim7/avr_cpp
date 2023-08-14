# AVR stub library for testing on dev system
if (NOT CMAKE_SYSTEM_NAME STREQUAL "Generic")
    add_subdirectory(avr_stub)
endif()