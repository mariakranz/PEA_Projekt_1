//
// Created by Szef on 14.10.2023.
//

#ifndef PEA_PROJEKT_1_SET_H
#define PEA_PROJEKT_1_SET_H


#include "../graphs/Graph.h"

class Set{
    setNode* setsTable;                     //tablica setow czyli drzew
    int size;
    void link(int x, int y);
public:
    Set(int verticesNumber);
    ~Set();
    void makeSet(int x);
    void unionSets(int x, int y);
    int findSet(int x);

    void printSetsTable();                  //funkcja pomocnicza - wyswietlanie setow

};


#endif //PEA_PROJEKT_1_SET_H
