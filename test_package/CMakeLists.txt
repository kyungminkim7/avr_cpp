cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)

find_package(avr_cpp CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example avr_cpp::avr_cpp)
