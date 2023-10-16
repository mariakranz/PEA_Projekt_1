cmake_minimum_required(VERSION 3.26)
project(PEA_Projekt_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_Projekt_1 main.cpp
        data/DataReader.cpp
        data/DataReader.h
        graphs/Graph.cpp
        graphs/Graph.h
        graphs/UndirectedGraph.cpp
        graphs/UndirectedGraph.h
        structures/Set.cpp
        structures/Set.h
        structures/PriorityQueue.cpp
        structures/PriorityQueue.h
        representations/GraphRep.cpp
        representations/GraphRep.h)
