cmake_minimum_required(VERSION 3.17)
project(_Bitonic_Sort)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(
        ${GTEST_INCLUDE_DIRS}
)

add_executable(Bitonic_Sort main.cpp Bitonic_sort.cpp Bitonic_sort.h)
add_executable(Test test/test_sort.cpp)

target_include_directories (Bitonic_Sort PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (Bitonic_Sort ${OpenCL_LIBRARY})

target_link_libraries(
        Test ${GTEST_LIBRARIES} Threads::Threads
)