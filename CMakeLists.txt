cmake_minimum_required(VERSION 3.31)
project(UGKS)

set(CMAKE_CXX_STANDARD 20)

add_executable(UGKS main.cpp
        matrix.cpp
        matrix.h
        problem.cpp
        problem.h
        evaluations.cpp
        evaluations.h
        updates.cpp
        updates.h
        solver.cpp
        solver.h
        result_export.cpp
        result_export.h
)
target_compile_options(UGKS PRIVATE -Wall -Wextra -Wpedantic)

