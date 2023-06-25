add_library(avr_cpp
    abstract.cpp
    memory.cpp
)

target_include_directories(avr_cpp PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)

target_compile_definitions(avr_cpp PUBLIC
    "F_CPU=${CPU_FREQ}"
    "BAUD=${BAUD}"
)

target_compile_options(avr_cpp PUBLIC
    "-fdata-sections"
    "-ffunction-sections"
    "-fno-exceptions"
)

if (CMAKE_SYSTEM_NAME STREQUAL "Generic")
    # AVR build options
    target_compile_options(avr_cpp PUBLIC "-mmcu=${MCU}")

    # Enable memory allocation/deallocation
    target_link_options(avr_cpp PUBLIC "LINKER:--defsym=__heap_end=0")
else()
    add_subdirectory(test)
endif()