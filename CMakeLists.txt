cmake_minimum_required(VERSION 3.6)
project(myPWD)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(myPWD ${SOURCE_FILES})

set(BOOST_ROOT "/${BOOST_ROOT}")

find_package(Boost 1.57.0)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()