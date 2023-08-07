include(Testing)

add_googletest(
    TARGET test_bit_op
    SOURCE_FILES test_bit_op.cpp
    LIBRARIES avr_cpp
)

add_googletest(
    TARGET test_port
    SOURCE_FILES test_port.cpp
    LIBRARIES avr_cpp
)

add_googletest(
    TARGET test_usart
    SOURCE_FILES test_usart.cpp
    LIBRARIES avr_cpp
)