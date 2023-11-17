//
// Created by Szef on 14.10.2023.
//

#include "DataReader.h"
#include <fstream>
#include <iostream>

DirectedGraph* DataReader::createGraphFromTheData(std::string filePath) {
    std::fstream file;
    file.open(filePath, std::ios::in);

    if(file.is_open()) {
        int verticesNumber = 0;

        file >> verticesNumber;
        if (file.fail()) {

            file.close();
            return nullptr;
        }
        int edgesNumber = (verticesNumber * verticesNumber - verticesNumber)/2;

        auto *graph = new DirectedGraph(verticesNumber, edgesNumber);

        int cost;
        int nth;
        for (int i = 0; i < verticesNumber; i++) {
            for (int j = 0; j < verticesNumber; j++){
                if ( i == j ){
                    file >> nth;
                } else{
                    file >> cost;

                    if(file.fail())
                    {
                        delete graph;
                        file.close();
                    }
                    graph->addEdge(i, j, cost);
                }
            }
        }

        file.close();
        return graph;
    }
    else
        return nullptr;
}

DirectedGraph *DataReader::createRandomGraph(int verticesNumber) {
    if (verticesNumber < 2) return nullptr;
    DirectedGraph *graph = new DirectedGraph(verticesNumber, verticesNumber*(verticesNumber - 1));

    for(int i = 0; i < verticesNumber; i++){
        for(int j = 0; j < verticesNumber; j++){
            if(i == j) continue;
            graph->addEdge(i, j, rand() % 100);        //koszty randomowe w przedziale [0, 100)
        }
    }

    return graph;
}
