include(Testing)

add_googletest(
    TARGET test_port
    SOURCE_FILES test_port.cpp
    LIBRARIES avr_cpp
)