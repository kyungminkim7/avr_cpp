# MCU-specific targets
if (CMAKE_SYSTEM_NAME STREQUAL "Generic")
    add_subdirectory(avr_cpp)

    add_subdirectory(app)
endif()
