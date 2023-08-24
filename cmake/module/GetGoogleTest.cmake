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