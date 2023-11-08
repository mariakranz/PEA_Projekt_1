#include <iostream>
#include <chrono>
#include "data/DataReader.h"
#include "representations/GraphRep.h"
#include "graphs/DirectedGraph.h"

using namespace std;

void menu();

int main() {
    cout << "Autorka: Maria Kranz, nr indeksu: 263985" << endl;
    menu();
    return 0;
}

void menu(){
    DataReader* dataReader = new DataReader();
    string filePath;
    DirectedGraph *graph = nullptr;
    char choice;
    int startV;

    do{
        cout << "\n----MENU----\n"
                "1. Wczytanie danych z pliku.\n"
                "2. Wygenerowanie danych losowych.\n"
                "3. Wyswietlenie danych.\n"
                "4. Algorytm Brute Force.\n"
                "5. Algorytm Branch and Bound.\n"
                "6. Algorytm DP.\n"
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

                //filePath = "..\\tsp_4.txt";

                graph = dataReader->createGraphFromTheData(filePath);
                if (graph != nullptr){
                    GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVeritcesNumber());
                }else{
                    cout << "Bledy przy odczytywaniu danych." << endl;
                }
                break;
            case '2':
                break;
            case '3':
                if (graph != nullptr){
                    GraphRep::printAdjacencyMatrix(graph->getAdjMatrix(), graph->getVeritcesNumber());
                    GraphRep::printAdjacencyList(graph->getAdjList(), graph->getVeritcesNumber());
                }else{
                    cout << "Brak danych." << endl;
                }
                break;
            case '4':
                if(graph){
                    cout << "Podaj wierzcholek startowy: ";
                    cin >> startV;

                    auto start = std::chrono::high_resolution_clock::now();
                    int val = graph->TSPBruteForce(startV);                       //ostatnio dodany wierzcholek z ktorego wychodzi krawedz
                    auto end = std::chrono::high_resolution_clock::now();

                    long dur = (long)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                    std::cout << "Czas wykonania: " << dur << " milisekundy" << std::endl;

                    if(val == 0 ){
                        cout << "Wartosc najkrotszej sciezki = " << graph->getTSPSum() << endl;
                        cout << startV;

                        int *route = graph->getTSPRoute();
                        for(int v = 0; v < graph->getVeritcesNumber() - 1; v++){
                            cout << " -> " << route[v];
                        }
                        cout << " -> " << startV << endl;
                    }else{
                        cout << "Bledny wierzcholek." << endl;
                    };
                }else{
                    cout << "Nie zaladowano grafu." << endl;
                }
                break;
            case '5':
                if(graph){

                    auto start = std::chrono::high_resolution_clock::now();
                    int val = graph->TSPBranchAndBound();
                    auto end = std::chrono::high_resolution_clock::now();
                    long dur = (long)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                    std::cout << "Czas wykonania: " << dur << " milisekundy" << std::endl;

                    cout << "Wartosc najkrotszej sciezki = " << val << endl;

                    int *route = graph->getTSPRouteBnB();
                    for(int v = 0; v < graph->getVeritcesNumber(); v++){
                        cout << route[v] << " -> ";
                    }

                    cout << "0" << endl;

                }else{
                    cout << "Nie zaladowano grafu." << endl;
                }
                break;
            case '6':
                graph->TSPDP();
                break;
        }
    }while (choice != '0');

    delete graph;
}