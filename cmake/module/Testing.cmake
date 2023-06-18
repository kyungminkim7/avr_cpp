# Fetch GoogleTest
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

option(INSTALL_GTEST "Install GTest" OFF)
option(INSTALL_GMOCK "Install GMock" OFF)

FetchContent_MakeAvailable(googletest)

# Utility functions for adding tests to CTest
include(CMakePackageConfigHelpers)
include(GoogleTest)

function(add_googletest)
    set(optionalArgs "")
    set(oneValueArgs TARGET)
    set(multipleValueArgs SOURCE_FILES LIBRARIES)
    cmake_parse_arguments(googletest
        "${optionalArgs}" "${oneValueArgs}" "${multipleValueArgs}" "${ARGV}"
    )

    add_executable(${googletest_TARGET} ${googletest_SOURCE_FILES})

    target_link_libraries(${googletest_TARGET} PRIVATE
        gtest
        gmock
        gtest_main
        ${googletest_LIBRARIES}
    )
    
    gtest_discover_tests(${googletest_TARGET})
endfunction()