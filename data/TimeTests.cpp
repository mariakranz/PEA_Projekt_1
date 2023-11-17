//
// Created by Szef on 30.10.2023.
//

#include <ios>
#include <chrono>
#include <iostream>
#include <fstream>
#include "TimeTests.h"
#include "../graphs/DirectedGraph.h"
#include "DataReader.h"

void TimeTests::testBruteForce(std::string folderPath) {
    std::string outputFileName = "testBruteForce.txt";
    std::cout << std::endl << std::endl << "testBruteForce" << std::endl;

    std::string fullpath = folderPath + outputFileName;
    std::ofstream file;
    file.open(fullpath, std::ios::out);

    if (file.is_open()) {
        file << "size;time[us]";                          //wpisywanie wiersza naglowkowego
        file << std::endl;

        DirectedGraph *graph;
        int vertNum;
        for (int graphs_size: graphs_sizes_bf) {

            vertNum = graphs_size;
            for (int j = 0; j < GRAPHS_NUMBER; j++) {

                std::cout << "Graf " << j << "rozmiar: " << vertNum << std::endl;

                graph = DataReader::createRandomGraph(vertNum);

                auto start = std::chrono::high_resolution_clock::now();
                graph->TSPBruteForce(0);
                auto end = std::chrono::high_resolution_clock::now();

                long dur = (long) std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                std::cout << "Czas wykonania: " << dur << " us." << std::endl;
                file << vertNum << ";" << dur << std::endl;

                delete graph;

            }
        }

    }
}

void TimeTests::testBranchAndBound(std::string folderPath) {
    std::string outputFileName = "testBranchAndBound.txt";
    std::cout << std::endl << std::endl << "testBranchAndBound" << std::endl;

    std::string fullpath = folderPath + outputFileName;
    std::ofstream file;
    file.open(fullpath, std::ios::out);

    if (file.is_open()) {
        file << "size;time[us]";                          //wpisywanie wiersza naglowkowego
        file << std::endl;

        DirectedGraph *graph;
        int vertNum;
        for (int graphs_size: graphs_sizes_bnb) {

            vertNum = graphs_size;
            for (int j = 0; j < GRAPHS_NUMBER; j++) {

                std::cout << "Graf " << j << "rozmiar: " << vertNum << std::endl;

                graph = DataReader::createRandomGraph(vertNum);

                auto start = std::chrono::high_resolution_clock::now();
                graph->TSPBranchAndBound();
                auto end = std::chrono::high_resolution_clock::now();

                long dur = (long) std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                std::cout << "Czas wykonania: " << dur << " us." << std::endl;
                file << vertNum << ";" << dur << std::endl;

                delete graph;

            }
        }

    }
}
