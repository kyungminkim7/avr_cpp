include(Testing)

add_googletest(
    TARGET test_bits
    SOURCE_FILES test_bit_op.cpp
    LIBRARIES avr_cpp
)

add_googletest(
    TARGET test_digital_pin_bank
    SOURCE_FILES test_digital_pin_bank.cpp
    LIBRARIES avr_cpp
)

add_googletest(
    TARGET test_usart
    SOURCE_FILES test_usart.cpp
    LIBRARIES avr_cpp
)