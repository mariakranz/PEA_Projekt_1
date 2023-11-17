//
// Created by Szef on 30.10.2023.
//

#ifndef PEA_PROJEKT_1_TIMETESTS_H
#define PEA_PROJEKT_1_TIMETESTS_H

#define INSTANCES_NUMBER_BF 7
#define INSTANCES_NUMBER_BNB 11
#define GRAPHS_NUMBER 100

class TimeTests {

    constexpr static const int graphs_sizes_bf[INSTANCES_NUMBER_BF] = { 8, 9, 10, 11, 12, 13, 14};

    constexpr static const int graphs_sizes_bnb[INSTANCES_NUMBER_BNB] = { 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 20};

public:
    static void testBruteForce(std::string folderPath);
    static void testBranchAndBound(std::string folderPath);
};

#endif //PEA_PROJEKT_1_TIMETESTS_H
