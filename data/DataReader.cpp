//
// Created by Szef on 14.10.2023.
//

#include "DataReader.h"
#include <fstream>
#include <iostream>

DataReader::DataReader() {
//    verticesNumber = edgesNumber = startVertex = endVertex = 0;
//    //edges = nullptr;
//    edgesTab = nullptr;
}

DataReader::~DataReader() {
    //verticesNumber = edgesNumber = startVertex = endVertex = 0;         //idk czy to ma sens
}

//int DataReader::getVerticesNumber() {
//    return verticesNumber;
//}
//
//int DataReader::getEdgesNumber() {
//    return edgesNumber;
//}
//
//int DataReader::getStartVertex() {
//    return startVertex;
//}
//
//int DataReader::getEndVertex() {
//    return endVertex;
//}
//
//int DataReader::readDataFromFile(std::string filePath) {
//    std::fstream file;
//    file.open(filePath, std::ios::in);
//    if(file.is_open()) {
//        //file >> edgesNumber;
//        file >> verticesNumber;
//        edgesNumber = (verticesNumber * verticesNumber - verticesNumber)/2;
//        //file >> startVertex;
//        //file >> endVertex;
//        if (file.fail()) {
//            //cout << "File error - READ SIZE" << stendl;
//            file.close();
//            return -1;
//        }
//
//        edgesTab = new edge [edgesNumber];
//        int index = 0;
//        for (int i = 0; i < verticesNumber; i++) {
//            for (int j = 0; j < verticesNumber; j++){
//                if( j >= i){
//                    edgesTab[index].tail = i;               //wierzcholek poczatkowy
//                    edgesTab[index].head = j;               //wierzcholek koncowy
//
//                    file >> edgesTab[index].cost;           //waga
//                    if(file.fail())
//                    {
//                        //cout << "File error - READ DATA" << endl;
//                        delete [] edgesTab;
//                        //delete edgesTab;
//                        file.close();
//                        return -1;
//                    }
//
//                    index ++;
//                }
//            }
//        }
//
//        file.close();
//        return 0;
//    }
//    else
//        //cout << "File error - OPEN" << endl;
//        return -1;
//}
//
//edge* DataReader::getEdges() {
//    return edgesTab;
//}

DirectedGraph* DataReader::createGraphFromTheData(std::string filePath) {
    std::fstream file;
    file.open(filePath, std::ios::in);

    if(file.is_open()) {
        int verticesNumber = 0;

        file >> verticesNumber;
        if (file.fail()) {

            file.close();
            return nullptr;
        }
        int edgesNumber = (verticesNumber * verticesNumber - verticesNumber)/2;

        auto *graph = new DirectedGraph(verticesNumber, edgesNumber);

        int cost;
        int nth;
        int index = 0;
        for (int i = 0; i < verticesNumber; i++) {
            for (int j = 0; j < verticesNumber; j++){
                if ( i == j ){
                    file >> nth;
                } else{
                    file >> cost;

                    if(file.fail())
                    {
                        delete graph;
                        file.close();
                    }
                    graph->addEdge(i, j, cost);
                }

//                if( i < j){
//                    int cost;
//                    file >> cost;
//
//                    if(file.fail())
//                    {
//                        delete &graph;
//                        file.close();
//                    }
//                    graph->addEdge(i, j, cost);
//                    index ++;
//                }
//                else{
//                    int nth;
//                    file >> nth;
//                }
            }
        }

        file.close();
        return graph;
    }
    else
        return nullptr;
}
