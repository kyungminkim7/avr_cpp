cmake_minimum_required(VERSION 3.20)
project(AvrCpp VERSION 1.0.0 LANGUAGES CXX)

#----------------------------
# Project Settings
#----------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/module")

#----------------------------
# Global Options
#----------------------------
set(MCU atmega168p CACHE STRING "Atmel microcontroller type")
set(CPU_FREQ 1000000UL CACHE STRING "Clock frequency")
set(BAUD 9600UL CACHE STRING "Baud rate")

set(PROGRAMMER_TYPE usbtiny CACHE STRING "Programmer type")

#----------------------------
# Subdirectories
#----------------------------
add_subdirectory(src bin)
