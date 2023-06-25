include(Testing)

add_googletest(
    TARGET test_digital_port
    SOURCE_FILES test_digital_port.cpp
    LIBRARIES avr_cpp
)

add_googletest(
    TARGET test_bits
    SOURCE_FILES test_bit_op.cpp
    LIBRARIES avr_cpp
)