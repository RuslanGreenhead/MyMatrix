cmake_minimum_required(VERSION 3.20)
project(Lab_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab_2
        Allocator.h
        Allocator_other.h
        check.cpp
        check.h
        main.cpp
        Matrix.h
        Matrix.hpp
        Matrix_utilites.hpp
        Matrix_utilities.h
        LinAlgError.h
        Matrix_utilites_additional.hpp
        Matrix_utilites_additional.h)
