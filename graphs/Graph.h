//
// Created by Szef on 14.10.2023.
//

#ifndef PEA_PROJEKT_1_GRAPH_H
#define PEA_PROJEKT_1_GRAPH_H


struct MSTEdge{                                 //krawedzie drzewa
    int tail, head, cost;
};

struct setNode{                                 //do klasy Set i PriorityQueue
    int rank, parent;
};

struct listNode{                                //element listy sąsiedztwa
    int vertex, cost;
    listNode* next;
};


class Graph {

protected:
    int verticesNumber;
    int** adjacencyMatrix;                      //macierz sąsiedztwa - tablica dwuwymiarowa
    listNode** adjacencyList;                   //lista sąsiedztwa - tablica list (tablica wskaznikow na struktury)
    int edgesNumber;
public:
    Graph(int verticesNumber, int edgesNumber);
    ~Graph();
    int** getAdjMatrix();
    listNode** getAdjList();
    int getVeritcesNumber();
};


#endif //PEA_PROJEKT_1_GRAPHREP_H
