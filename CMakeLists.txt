cmake_minimum_required(VERSION 3.5)
project(intouch_test_v1)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/string_calculator)

set(SOURCE_FILES main.cpp string_calculator/CStringCalculator.cpp)
add_executable(intouch_test_v1 ${SOURCE_FILES})