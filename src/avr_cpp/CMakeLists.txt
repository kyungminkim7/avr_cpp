include(GetETL)

add_library(avr_cpp
    analog_digital_converter.cpp
    abstract.cpp
    memory.cpp
)

# Generate USART source/header files
MATH(EXPR USART_END "${NUM_USART_MODULES}-1")
foreach(n RANGE ${USART_END})
    configure_file(usartn.h.in "include/avr_cpp/usart${n}.h")
    configure_file(usartn.cpp.in "${CMAKE_CURRENT_BINARY_DIR}/usart${n}.cpp")
    target_sources(avr_cpp PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/usart${n}.cpp")
endforeach()

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