cmake_minimum_required(VERSION 3.17)
project(triangle)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(
        ${GTEST_INCLUDE_DIRS}
)

add_executable(
        triangle
        main.cpp
        Triangle.cpp
        Triangle.h
)

add_executable(
        testTriangle
        Test/test_triangle.cpp
        Triangle.cpp
)

target_link_libraries(
        testTriangle ${GTEST_LIBRARIES} Threads::Threads)

