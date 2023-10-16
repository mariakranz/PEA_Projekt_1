#include <iostream>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graphs/UndirectedGraph.h"

using namespace std;

void menu();
void insertDataToTheGraph(DataReader *fileData, UndirectedGraph *&graph);

int main() {
    cout << "Autorka: Maria Kranz, nr indeksu: 263985" << endl;
    menu();
    return 0;
}

void menu(){
    DataReader* dataReader = new DataReader();
    string filePath;
    UndirectedGraph *graph = nullptr;
    char choice;

    do{
        cout << "\n----MENU----\n"
                "1. Wczytanie danych z pliku.\n"
                "2. Algorytm Brute Force.\n"
                "0. Wyjdz z programu.\n"
                "Wprowdz numer: ";
        cin >> choice;
        switch (choice) {
            default:
                cout << "Nie ma takiej opcji!\n";
                break;
            case '0': break;
            case '1':
                cout << "Podaj nazwe pliku: ";
                cin >> filePath;
                //filePath = "..\\tsp_10.txt";
                //dataReader->readDataFromFile(filePath);

                //insertDataToTheGraph(dataReader, graph);
                graph = dataReader->createGraphFromTheData(filePath);
                GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVeritcesNunber());
                break;
            case '2':
                //
                break;
        }
    }while (choice != '0');

    delete graph;
}

//void insertDataToTheGraph(DataReader *fileData, UndirectedGraph *&graph) {
//    int verticesNum = 0;
//    verticesNum = fileData->getVerticesNumber();
//    graph = new UndirectedGraph(verticesNum, fileData->getEdgesNumber());
//    edge* data = fileData->getEdges();
//    for (int i = 0; i < fileData->getEdgesNumber(); i++) {
//        edge edgeData = data[i];
//        graph->addEdge(edgeData.tail, edgeData.head, edgeData.cost);
//    }
//}