# AVR stub library for unit testing on host machine builds
add_subdirectory(avr_cpp)

if (CMAKE_SYSTEM_NAME STREQUAL "Generic")
    add_subdirectory(app)
endif()
