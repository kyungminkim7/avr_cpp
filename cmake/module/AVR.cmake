function(AddExecutableAVR)
    set(oneValueArgs NAME)
    set(multiValueArgs 
            SOURCES INCLUDE_DIRECTORIES LIBRARIES 
            COMPILE_DEFINITIONS COMPILE_OPTIONS LINK_OPTIONS)
    cmake_parse_arguments(AVR "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # File outputs
    set(elf_file "${AVR_NAME}.elf")
    set(map_file "${AVR_NAME}.map")
    set(hex_file "${AVR_NAME}.hex")
    set(lst_file "${AVR_NAME}.lst")

    # Executable target
    add_executable("${elf_file}" "${AVR_SOURCES}")

    target_include_directories("${elf_file}" PRIVATE "${AVR_INCLUDE_DIRECTORIES}")

    target_link_libraries("${elf_file}" PRIVATE "${AVR_LIBRARIES}")

    target_compile_definitions("${elf_file}" PRIVATE "${AVR_COMPILE_DEFINITIONS}")

    target_compile_options("${elf_file}" PRIVATE "${AVR_COMPILE_OPTIONS}")

    target_link_options("${elf_file}" PRIVATE 
        "${AVR_LINK_OPTIONS}"
        "LINKER:-Map,${map_file}"
    )

endfunction()
