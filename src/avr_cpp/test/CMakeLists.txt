include(CMakePackageConfigHelpers)
include(GoogleTest)

include(GetGoogleTest)

add_subdirectory(avr_cpp_test)

function(add_avr_test)
    set(optionalArgs "")
    set(oneValueArgs TARGET SOURCE)
    set(multipleValueArgs "")
    cmake_parse_arguments(AVRTEST
        "${optionalArgs}" "${oneValueArgs}" "${multipleValueArgs}" "${ARGV}"
    )

    add_executable(${AVRTEST_TARGET} ${AVRTEST_SOURCE})
    target_link_libraries(${AVRTEST_TARGET} 
        avr_cpp_test
        gmock
        gtest
        gtest_main
    )
    gtest_discover_tests(${AVRTEST_TARGET})
endfunction()

add_avr_test(TARGET test_analog_digital_converter 
             SOURCE test_analog_digital_converter.cpp)

add_avr_test(TARGET test_bit
             SOURCE test_bit.cpp)

add_avr_test(TARGET test_external_interrupt 
             SOURCE test_external_interrupt.cpp)

add_avr_test(TARGET test_pin_change_interrupt 
             SOURCE test_pin_change_interrupt.cpp)

add_avr_test(TARGET test_port 
             SOURCE test_port.cpp)

add_avr_test(TARGET test_usart 
             SOURCE test_usart.cpp)