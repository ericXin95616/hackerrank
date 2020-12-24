cmake_minimum_required(VERSION 3.15)
project(hackerrank)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest CONFIG REQUIRED)
set(TARGET hackerrank)
add_executable(${TARGET} DP/wordBreakII.cpp)
target_link_libraries(${TARGET} GTest::gtest GTest::gmock)