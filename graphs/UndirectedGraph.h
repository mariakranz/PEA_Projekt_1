//
// Created by Szef on 14.10.2023.
//

#ifndef PEA_PROJEKT_1_UNDIRECTEDGRAPH_H
#define PEA_PROJEKT_1_UNDIRECTEDGRAPH_H


#include "Graph.h"


#include <string>
#include <vector>

enum color{WHITE, GREY, BLACK};                                     //do DFS

class UndirectedGraph : public Graph {

    void DFSVisit(int u, color *&colors, int *&parents, int time);

private:
    int startV;
    int TSPSum;
    int *TSPRoute;

public:
    UndirectedGraph(int verticesNumber, int edgesNumber);
    ~UndirectedGraph();




    void addEdge(int tail, int head, int cost);                     //tail - wierzcholek poczatkowy, head - wierzcholek koncowy
    bool changeAlreadyDefinedEdge(int tail, int head, int cost);

    int DFS();
    bool isConnected();                                             //czy graf jest spojny

    MSTEdge* MSTKruskalAdjMatrix();
    MSTEdge* MSTKruskalAdjList();
    MSTEdge* MSTPrimAdjMatrix(int r);                               //r - wierzcholek od ktorego zaczynamy wyznaczanie drzewa
    MSTEdge* MSTPrimAdjList(int r);


    void swap(int &a, int&b);
    void generatePermutations(int *verticesTable, int currentIndex);
    int TSPBruteForce(int startVertex);
    int getTSPSum();
    int* getTSPRoute();
};


#endif //PEA_PROJEKT_1_UNDIRECTEDGRAPH_H
