//
// Created by Szef on 14.10.2023.
//

#ifndef PEA_PROJEKT_1_GRAPHREP_H
#define PEA_PROJEKT_1_GRAPHREP_H


#include "../graphs/Graph.h"

class GraphRep {
public:
    static void printAdjacencyMatrix(int **table, int verticesNum);
    static void printAdjacencyList(listNode **listTable, int verticesNum);
};


#endif //PEA_PROJEKT_1_GRAPHREP_H
