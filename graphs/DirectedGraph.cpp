//
// Created by Szef on 14.10.2023.
//

#include <valarray>
#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int verticesNumber, int edgesNumber) : Graph(verticesNumber, edgesNumber) {
    this->verticesNumber = verticesNumber;
    this->edgesNumber = edgesNumber;

    TSPRoute = new int[verticesNumber];
    tspParentsRoute = new int [verticesNumber];

}

DirectedGraph::~DirectedGraph() {
    delete [] TSPRoute;
    delete [] tspParentsRoute;
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
    int TSPSum = INT_MAX;

    int *numbers = new int[verticesNumber-1];

    int iterator = 0;
    for(int i = 0; i  < verticesNumber; i++){

        if(i == startVertex) continue;
        numbers[iterator] = i;
        iterator++;

    }

    TSPRoute[0] = startVertex;                                                                  //elementam pierwszym cyklu jest wierzcholek startowy
    generatePermutations(numbers, 0, TSPSum, startVertex);
    return TSPSum;
}

void DirectedGraph::swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void DirectedGraph::generatePermutations(int *verticesTable, int currentIndex, int &TSPSum, int startV) {
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
            for(int i = 1; i < verticesNumber; i++){
                TSPRoute[i] = verticesTable[i - 1];
            }
        }
        return;
    }

    for (int i = currentIndex; i < numbersCount; ++i){
        swap(verticesTable[currentIndex], verticesTable[i]);
        generatePermutations(verticesTable, currentIndex + 1, TSPSum, startV);
        swap(verticesTable[currentIndex], verticesTable[i]);
    }
}

int *DirectedGraph::getTSPRoute() {         //najpierw trzeba wywolac TSPBruteForce(int startVertex)
    return TSPRoute;
}

void DirectedGraph::DFSVisit(int u, color *&colors, int *&parents, int lowerBound, int &upperBound, int *&helperTab) {

    colors[u] = GREY;
    bool isLeaf = true;
    for(int v = 0; v < verticesNumber; v++){
        if(v == u) continue;
        if(colors[v] == WHITE){
            isLeaf = false;
            int newLowerBound = lowerBound - helperTab[u] + adjacencyMatrix[u][v];
            if(newLowerBound < upperBound){
                parents[v] = u;
                DFSVisit(v, colors, parents, newLowerBound, upperBound, helperTab);
            }
        }
    }

    colors[u] = WHITE;
    if(isLeaf){

        int path = lowerBound - helperTab[u] + adjacencyMatrix[u][0];
        if (path < upperBound){
            upperBound = path;                                              //ustawia nowa gorna granice
            for(int i = 0; i < verticesNumber; i++){
                tspParentsRoute[i] = parents[i];
            }                                                               //zapamietuje granice i sciezka
        }
    }
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

    color* colors = new color[verticesNumber];
    int* parents = new int[verticesNumber];

    for (int i = 0; i < verticesNumber; i++){
        colors[i] = WHITE;
        parents[i] = -1;
    }

    DFSVisit(0, colors, parents, lowerBound, upperBound, helperTab);

    delete [] colors;
    delete [] parents;
    return upperBound;
}

int *DirectedGraph::getTSPRouteBnB() {
    if(tspParentsRoute == nullptr) return nullptr;      //najpierw trzeba wywolac TSPBranchAndBound()
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