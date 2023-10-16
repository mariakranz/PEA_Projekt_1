//
// Created by Szef on 14.10.2023.
//

#ifndef PEA_PROJEKT_1_DATAREADER_H
#define PEA_PROJEKT_1_DATAREADER_H

#include <string>
#include "../graphs/UndirectedGraph.h"

//struct edge{
//    int tail;       //tail -> head
//    int head;
//    int cost;
//};

class DataReader {
//    int verticesNumber;
//    int edgesNumber;
//    int startVertex;
//    int endVertex;
//    //int **edges;
//    edge* edgesTab;     //wskaznik na tablice struktur

public:
    DataReader();
    ~DataReader();

//    int readDataFromFile(std::string fileName);
//    int getVerticesNumber();
//    int getEdgesNumber();
//    int getStartVertex();
//    int getEndVertex();
//    edge* getEdges();

    UndirectedGraph* createGraphFromTheData(std::string filePath);
};


#endif //PEA_PROJEKT_1_DATAREADER_H
