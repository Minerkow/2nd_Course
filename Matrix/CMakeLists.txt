cmake_minimum_required(VERSION 2.8)
project(Matrix)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(
        ${GTEST_INCLUDE_DIRS}
)

add_executable(Matrix
               main.cpp
               Matrix.hpp)

add_executable(test_matrix
               ./test/test_matrix.cpp
               test/test_generator.hpp
               Matrix.hpp)

target_link_libraries(
        test_matrix ${GTEST_LIBRARIES} Threads::Threads
)