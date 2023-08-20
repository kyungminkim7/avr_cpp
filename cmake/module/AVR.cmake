find_program(AVR_OBJCOPY avr-objcopy REQUIRED)
find_program(AVR_SIZE avr-size REQUIRED)
find_program(AVR_FLASH avrdude REQUIRED)

function(AddExecutableAVR)
    set(oneValueArgs TARGET MCU PROGRAMMER_TYPE)
    set(multiValueArgs 
            SOURCES INCLUDE_DIRECTORIES LIBRARIES 
            COMPILE_DEFINITIONS COMPILE_OPTIONS LINK_OPTIONS)
    cmake_parse_arguments(AVR "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Validate arguments
    if(NOT DEFINED AVR_TARGET)
        message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION} - TARGET not provided")
    endif()

    if(NOT DEFINED AVR_MCU)
        message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION} - MCU not provided")
    endif()

    if(NOT DEFINED AVR_PROGRAMMER_TYPE)
        message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION} - PROGRAMMER_TYPE not provided")
    endif()

    if(NOT DEFINED AVR_SOURCES)
        message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION} - SOURCES not provided")
    endif()

    # File outputs
    set(elf_file "${AVR_TARGET}.elf")
    set(hex_file "${AVR_TARGET}.hex")

    # Executable target
    add_executable("${elf_file}" EXCLUDE_FROM_ALL "${AVR_SOURCES}")

    target_include_directories("${elf_file}" PRIVATE "${AVR_INCLUDE_DIRECTORIES}")

    target_link_libraries("${elf_file}" PRIVATE "${AVR_LIBRARIES}")

    target_compile_definitions("${elf_file}" PRIVATE "${AVR_COMPILE_DEFINITIONS}")

    target_compile_options("${elf_file}" PRIVATE "${AVR_COMPILE_OPTIONS}")

    target_link_options("${elf_file}" PRIVATE "${AVR_LINK_OPTIONS}")

    # Create hex file
    add_custom_command(
        OUTPUT "${hex_file}"
        COMMAND "${AVR_OBJCOPY}" -O ihex -R .eeprom "${elf_file}" "${hex_file}"
        DEPENDS "${elf_file}"
    )

    # Print elf file size and Flash AVR
    add_custom_target("${AVR_TARGET}"
        COMMAND "${AVR_SIZE}" -C "--mcu=${AVR_MCU}" "${elf_file}"
        COMMAND "${AVR_FLASH}" -c "${AVR_PROGRAMMER_TYPE}" -p "${AVR_MCU}" -U "flash:w:${hex_file}:i"
        DEPENDS "${hex_file}"
    )

endfunction()
