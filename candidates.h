#ifndef CANDIDATES_H
#define CANDIDATES_H

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

class Candidates {
public:
    Candidates();
    ~Candidates();

    void loadCandidates(std::ifstream& infile, std::string candidates[][6], int num_candidates);
    void addCandidate(std::string candidates[][6], int size);
    void getCandidate(std::string candidate[6]);
    void saveCandidates(std::string temp[][6], int size);
    void printCandidates(std::string candidates[][6], int size);
    void showCandidatesByPosition(std::string candidates[][6], int size);
    void sortByRating(std::string candidates[][6], int num_candidates);
    void filterCandidatesByRating(std::string candidates[][6], int num_candidates);
    void printCandidate(std::string candidates[][6], int index);
    void swapCandidates(std::string candidates[][6], int indexA, int indexB);
    void findCandidateById(std::string candidates[][6], int size, const std::string& id);

private:
    std::string candidatesData[100][6];
};

#endif // CANDIDATES_H
