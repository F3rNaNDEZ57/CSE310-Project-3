cmake_minimum_required(VERSION 3.27)
project(Final)

set(CMAKE_CXX_STANDARD 17)

add_executable(Final main.cpp
        data_structures.cpp
        data_structures.h
        heap.cpp
        heap.h
        stack.cpp
        stack.h
        graph.cpp
        graph.h
        util.cpp
        util.h)
