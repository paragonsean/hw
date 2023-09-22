#ifndef CANDIDATES_H
#define CANDIDATES_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <filesystem>
using namespace std;

class candidates {
public:
    std::string (*candidatearray)[6]; 
    int num_of_candidates;
    candidates();
    candidates(int numOfCandidates);
    candidates(string filename);
    ~candidates();
    void PrintCandidates();
    void AddCandidate();
    void PrintCandidates(std::string candidates[][6], int size);
    void AddCandidate(std::string candidates[][6], int size);
    void FilterCandidatesByRating();
    void ShowCandidatesByPosition();

    void SetSize(int size);
    int GetSize();
    bool FileExists(const std::string& filename);
    void FileOpenFile(ifstream& infile, string filename);
    string GetFileName();
    string GetCandidates();
    void LoadCandidates(std::ifstream& infile, std::string candidates[][6], int num_candidates);
    void FilterCandidatesByRating(string candidates[][6], int num_candidates);
    void ShowCandidatesByPosition(string candidates[][6], int size);
    void SwapCandidates(std::string candidates[][6], int indexA, int indexB);
    void GetCandidate(std::string candidate[6]);
    void SaveCandidates(std::string candidates[][6], int size);
    void PrintCandidate(string candidates[][6], int index);
    void ResetIDs(std::string candidates[][6], int size);
    int StringToInt(std::string s);
    std::string IntToString(int i);
    void LoadCandidates(std::ifstream& infile);
   
};
#endif