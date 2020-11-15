cmake_minimum_required(VERSION 2.8)
project(ParaCL)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        ParaCL
        numgrammar.tab.cc
        lex.yy.cc
        driver.cc
        numdriver.hpp
)