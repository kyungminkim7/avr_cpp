include(FetchContent)

option(NO_SYSTEM_INCLUDE "Do not include with -isystem" ON)

FetchContent_Declare(
    etl
    GIT_REPOSITORY https://github.com/ETLCPP/etl
    GIT_TAG        master
)

FetchContent_MakeAvailable(etl)