cmake_minimum_required(VERSION 3.27)
project(Triangulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(Triangulation main.cpp
        Graph.cpp
        Graph.h
        vertex.cpp
        triangle.cpp
        vertex.h
        ThreadGraph.cpp
        ThreadGraph.h
        triangle.h
        DataHelper.cpp
        DataHelper.h
)
