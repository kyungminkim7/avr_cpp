if (NOT CMAKE_SYSTEM_NAME STREQUAL "Generic")
    # AVR stub library for testing on dev system
    add_subdirectory(avr_stub)
endif()