cmake_minimum_required(VERSION 3.26)
project(PEA_Projekt_1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(PEA_Projekt_1 main.cpp
        data/DataReader.cpp
        data/DataReader.h
        graphs/Graph.cpp
        graphs/Graph.h
        graphs/DirectedGraph.cpp
        graphs/DirectedGraph.h
        representations/GraphRep.cpp
        representations/GraphRep.h
        data/TimeTests.cpp
        data/TimeTests.h
)
