//
// Created by Szef on 14.10.2023.
//

#ifndef PEA_PROJEKT_1_DIRECTEDGRAPH_H
#define PEA_PROJEKT_1_DIRECTEDGRAPH_H


#include "Graph.h"


#include <string>
#include <vector>

enum color{WHITE, GREY};                                     //do DFS

class DirectedGraph : public Graph {

    void DFSVisit(int u, color *&colors, int *&parents, int lowerBound, int &upperBound, int *&helperTab);            //dfs O(V+E)

private:
    int *TSPRoute;
    void swap(int &a, int&b);
    void generatePermutations(int *verticesTable, int currentIndex, int &TSPSum, int startV);

    int * tspParentsRoute;                                          //do zapisania sciezki w BnB

public:
    DirectedGraph(int verticesNumber, int edgesNumber);
    ~DirectedGraph();

    void addEdge(int tail, int head, int cost);                     //tail - wierzcholek poczatkowy, head - wierzcholek koncowy
    bool changeAlreadyDefinedEdge(int tail, int head, int cost);

    int TSPBruteForce(int startVertex);                             //zlozonosc O((n-1)!)
    int* getTSPRoute();

    int TSPBranchAndBound();
    int* getTSPRouteBnB();
};


#endif //PEA_PROJEKT_1_DIRECTEDGRAPH_H
