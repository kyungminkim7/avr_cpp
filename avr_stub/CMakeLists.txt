target_sources(avr_cpp PUBLIC
    src/io.cpp
    src/interrupt.cpp
)

target_include_directories(avr_cpp PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

# Install stub headers
include(GNUInstallDirs)

install(
    DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
)
