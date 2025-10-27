cmake_minimum_required(VERSION 3.31)
project(UGKS CXX)

set(CMAKE_CXX_STANDARD 20)
# Change output directory to project directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(UGKS main.cpp
        matrix.cpp
        matrix.hpp
        problem.cpp
        problem.hpp
        evaluations.cpp
        evaluations.hpp
        collision.cpp
        collision.hpp
        discretization.hpp
)
target_compile_options(UGKS PRIVATE -Wall -Wextra -Wpedantic)

