//
// Created by Szef on 14.10.2023.
//

#include <iostream>
#include <valarray>
#include "DirectedGraph.h"
#include "../structures/PriorityQueue.h"

DirectedGraph::DirectedGraph(int verticesNumber, int edgesNumber) : Graph(verticesNumber, edgesNumber) {
    this->verticesNumber = verticesNumber;
    this->edgesNumber = edgesNumber;

    TSPSum = INT_MAX;
    TSPRoute = new int[verticesNumber - 1];
    startV = -1;

    visitedAll = (1<<verticesNumber) - 1;

    //dp = new int*[pow(2, verticesNumber)][3];
    int num = (int)pow((double)2, (double)verticesNumber);
    dp = new int *[num];
    for(int i = 0; i < (1<<verticesNumber); i++){
        dp[i] = new int[verticesNumber];
        for(int j = 0; j < verticesNumber; j ++){
            dp[i][j] = -1;
        }
    }

    //upperBound = INT_MAX;
    tspParentsRoute = new int [verticesNumber];
}

DirectedGraph::~DirectedGraph() {
    delete [] TSPRoute;

    for(int i = 0; i < (1<<verticesNumber); i++){
        delete [] dp[i];
    }
    delete [] dp;
}

void DirectedGraph::addEdge(int tail, int head, int cost) {
    if (head == tail) {
        edgesNumber--;                                                              //zalozenia, takie jak przy grafie nieskierowanym
        return;
    }
    adjacencyMatrix[tail][head] = cost;                                             //dodawanie do macierzy sasiedztwa

    if (changeAlreadyDefinedEdge(tail, head, cost)) return;                         //jesli znajdzie juz taka krawedz, to ja nadpisuje
    listNode* newNode = new listNode{head, cost, adjacencyList[tail]};  //w przeciwnym wypadku tworzy nowy wezel
    adjacencyList[tail] = newNode;
}

bool DirectedGraph::changeAlreadyDefinedEdge(int tail, int head, int cost) {
    listNode* n = adjacencyList[tail];
    while(n){
        if(n->vertex == head) {                     //jesli zanjdzie juz definicje danej krawedzi
            n->cost = cost;                         //nadpisuje wage, nowa wartoscia

            listNode* p = adjacencyList[head];
            while(p->vertex != tail)p = p->next;    //ustaw p na element do nadpisania
            p->cost = cost;                         //nadpisuje wage
            edgesNumber--;
            return true;
        }
        n = n->next;
    }
    return false;
}

int DirectedGraph::TSPBruteForce(int startVertex) {
    if (startVertex < 0 || startVertex > verticesNumber - 1) return 1;
    TSPSum = INT_MAX;
    startV = startVertex;

    int *numbers = new int[verticesNumber-1];

    int iterator = 0;
    for(int i = 0; i  < verticesNumber; i++){

        if(i == startVertex) continue;
        numbers[iterator] = i;
        iterator++;

    }
    generatePermutations(numbers, 0);
    return 0;
}

void DirectedGraph::swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void DirectedGraph::generatePermutations(int *verticesTable, int currentIndex) {
    int numbersCount = verticesNumber-1;
    int tmp_sum = 0;

    if (currentIndex == numbersCount){
        tmp_sum += adjacencyMatrix[startV][verticesTable[0]];
        for (int i = 0; i < numbersCount - 1; i++){
            tmp_sum += adjacencyMatrix[verticesTable[i]][verticesTable[i+1]];
        }
        tmp_sum += adjacencyMatrix[verticesTable[numbersCount-1]][startV];

        if (tmp_sum < TSPSum){
            TSPSum = tmp_sum;
            for(int i = 0; i < numbersCount; i++){
                TSPRoute[i] = verticesTable[i];
            }
        }
        return;
    }

    for (int i = currentIndex; i < numbersCount; ++i){
        swap(verticesTable[currentIndex], verticesTable[i]);
        generatePermutations(verticesTable, currentIndex + 1);
        swap(verticesTable[currentIndex], verticesTable[i]);
    }
}

int DirectedGraph::getTSPSum() {
    return TSPSum;
}

int *DirectedGraph::getTSPRoute() {
    return TSPRoute;
}

int DirectedGraph::TSPDP() {


    std::cout << "min sciezka = " << tsp(1,0) << std::endl;
    return 0;
}

int DirectedGraph::tsp(int mask, int pos) {

    if(mask == visitedAll){
        return adjacencyMatrix[pos][0];
    }

    if(dp[mask][pos] != -1){
        return dp[mask][pos];
    }
    int ans = INT_MAX;

    for(int city = 0; city < verticesNumber; city++){

        if((mask&(1<<city))==0){

            int newAns = adjacencyMatrix[pos][city] + tsp(mask|(1<<city), city);
            ans = std::min(ans, newAns);
        }
    }
    return dp[mask][pos] = ans;
}


reduce *DirectedGraph::reduceAndCalculateBound(int **adjMatrix) {
    //dla kazdego wiersza znajdz min i odejmij

    for(int wiersz = 0; wiersz < verticesNumber; wiersz++){
        int min = INT_MAX;
        for(int kolumna = 0; kolumna < verticesNumber; kolumna++){
            if (adjMatrix[wiersz][kolumna] < min) min = adjMatrix[wiersz][kolumna];
        }

        if(min != INT_MAX || min != 0){
            for(int kolumna = 0; kolumna < verticesNumber; kolumna++){
                adjMatrix[wiersz][kolumna] -= min;
            }
        }
    }



    return nullptr;
}

void DirectedGraph::DFSVisit(int u, color *&colors, int *&parents, int time, int lowerBound, int &upperBound, int *&helperTab) {
    int *d = new int[verticesNumber];
    int *f = new int[verticesNumber];

    colors[u] = GREY;
    d[u] = time = time+1;
    listNode* v = adjacencyList[u];
    bool isLeaf = true;
    while(v){
        if(colors[v->vertex] == WHITE){
            isLeaf = false;
            int newLowerBound = lowerBound - helperTab[u] + v->cost;
            if(newLowerBound < upperBound){
                parents[v->vertex] = u;
                DFSVisit(v->vertex, colors, parents, time, newLowerBound, upperBound, helperTab);
            }
        }
        v = v->next;
    }

    colors[u] = WHITE;
    if(isLeaf){
        int path = lowerBound - helperTab[u] + adjacencyMatrix[u][0];
        if (path < upperBound){
            upperBound = path;      //ustaw nowa gorna granice
            for(int i = 0; i < verticesNumber; i++){
                tspParentsRoute[i] = parents[i];
            }           //zapamietaj granice i sciezka
        }
    }
    f[u] = time = time+1;
}

int DirectedGraph::TSPBranchAndBound() {
    int lowerBound = 0;
    int upperBound = INT_MAX;

    int* helperTab = new int[verticesNumber];
    for(int i = 0; i < verticesNumber; i++){
        int min = INT_MAX;
        for(int j = 0; j < verticesNumber; j++){
            if (i == j) continue;
            if (adjacencyMatrix[i][j] < min) min = adjacencyMatrix[i][j];
        }
        helperTab[i] = min;
        lowerBound += min;
    }
                                               //ilosc drzew, czyli osobnych sciezek
    color* colors = new color[verticesNumber];
    int* parents = new int[verticesNumber];
    int  time;

    for (int i = 0; i < verticesNumber; i++){
        colors[i] = WHITE;
        parents[i] = -1;
    }
    time = 0;

    DFSVisit(0, colors, parents, time, lowerBound, upperBound, helperTab);

    return upperBound;
}

int *DirectedGraph::getTSPRouteBnB() {
    int *tab = new int [verticesNumber];

    //znajdź -1 i wstaw do tab na pierwszą pozycje
    int ver = 0;
    for(; ver < verticesNumber; ver++){
        if(tspParentsRoute[ver] == -1) {                    //na razie zawsze dla 0
            tab[0] = ver;
            break;
        }
    }

    for(int i = 1; i < verticesNumber; i++){
        for (int j = 0; j <verticesNumber; j++){
            if(tspParentsRoute[j] == tab[i - 1]){
                tab[i] = j;
                break;
            }
        }
    }
    return tab;
}
