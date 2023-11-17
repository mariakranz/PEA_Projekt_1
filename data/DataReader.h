//
// Created by Szef on 14.10.2023.
//

#ifndef PEA_PROJEKT_1_DATAREADER_H
#define PEA_PROJEKT_1_DATAREADER_H

#include <string>
#include "../graphs/DirectedGraph.h"

class DataReader {

public:
    static DirectedGraph* createGraphFromTheData(std::string filePath);
    static DirectedGraph* createRandomGraph(int verticesNumber);
};


#endif //PEA_PROJEKT_1_DATAREADER_H
