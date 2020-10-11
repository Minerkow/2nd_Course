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
        IntersectionTriangles.h
        IntersectionTriangles.cpp
)

add_executable(
        testTriangle
        Test/test_triangle.cpp
        Test/test_intersection.cpp
        Triangle.cpp
        IntersectionTriangles.cpp
        Test/test_generator.cpp
        Test/test_generator.h
)

target_link_libraries(
        testTriangle ${GTEST_LIBRARIES} Threads::Threads
)

