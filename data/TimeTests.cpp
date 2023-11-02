//
// Created by Szef on 30.10.2023.
//

#include <ios>
#include "TimeTests.h"

using namespace std;

//int TimeTests::testDijkstraList() {
//    string filename = "DijkstraList_results.txt";
//
//    string fullpath = directory + filename;
//    ofstream file;
//    file.open(fullpath, std::ios::out);
//    if(file.is_open()){
//        file << "density";                          //wpisywanie wiersza naglowkowego
//        for(int i = 0; i < VERTNUM; i++){
//            file << ";size" << vertNum[i];
//        }
//        file << endl;
//
//        for(int i = 0; i < DENNUM; i++){
//            for (int k = 0; k < NUMTINST; k++){
//                file << density[i];
//                for (int j = 0; j < VERTNUM; j++){
//                    int verticesNum = vertNum[j];
//                    int maxUndirectedEdges = (verticesNum * (verticesNum - 1));
//                    int edgesNum = maxUndirectedEdges * density[i] / 100;
//
//                    DirectedGraph* graph = new DirectedGraph(verticesNum, edgesNum);
//
//                    edgeT* takenEdges = new edgeT[edgesNum];
//                    int edgeNR = 0;
//                    int tail;
//                    int head;
//
//                    for(; edgeNR < edgesNum; edgeNR++){
//                        do{
//                            tail = rand() %verticesNum;
//                            do{
//                                head = rand() %verticesNum;
//                            }while(tail == head);
//
//                        }while (isEdgeTaken(tail, head, takenEdges, edgesNum));
//                        takenEdges[edgeNR] = {tail, head};
//                        graph->addEdge(tail, head, rand() % edgesNum + 1);
//                    }
//
//                    std::cout << "Graf " << k << " - density: " << density[i] << "rozmiar: " << vertNum[j] << endl;
//
//                    auto start = std::chrono::high_resolution_clock::now();
//                    graph->DijkstraAdjList(rand() % verticesNum);                       //ostatnio dodany wierzcholek z ktorego wychodzi krawedz
//                    auto end = std::chrono::high_resolution_clock::now();
//
//                    long dur = (long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//                    std::cout << "Czas wykonania: " << dur << " nanosekundy" << std::endl;
//                    file << ";" << dur;
//
//                    delete graph;
//                    delete [] takenEdges;
//                }
//                file << endl;
//            }
//        }
//    }else {
//        cout << "Nie udalo sie odtworzyc pliku." << endl;
//        return - 1;
//    }
//
//    file.close();
//    return 0;
//}