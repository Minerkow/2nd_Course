cmake_minimum_required(VERSION 2.8)
project(triangle)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(
        ${GTEST_INCLUDE_DIRS}
)
add_executable(
                ParaCL
                main.cpp
                Parser.h
                Parser.cpp
                Lexer.h
                Lexer.cpp
              )

add_executable(
                TestParaCl
                Parser.cpp
                Lexer.cpp
                Test/test_lexer.cpp
                Test/test_parser.cpp
              )

target_link_libraries(
        TestParaCl ${GTEST_LIBRARIES} Threads::Threads
)