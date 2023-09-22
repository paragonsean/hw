#ifndef OPENINGS_H
#define OPENINGS_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <filesystem>
using namespace std;

class Openings {
public:
    std::string (*openings)[7]; 
    int num_of_openings;
    Openings();
    Openings(int numOfOpenings);
    Openings(string filename);
    ~Openings();
    void PrintOpenings();
    void AddOpening();
    void DeleteOpening();
    void PrintOpenings(std::string openings[][7], int size);
    void AddOpening(std::string openings[][7], int size);
    void DeleteOpening(std::string openings[][7], int size);


    void SetSize(int size);
    int GetSize();
    bool FileExists(const std::string& filename);
    void FileOpenFile(ifstream& infile, string filename);
    string GetFileName();
    string GetOpenings();
    void LoadOpenings(std::ifstream& infile, std::string openings[][7], int num_openings);
    
    void SwapOpenings(std::string openings[][7], int indexA, int indexB);
    void GetOpening(std::string opening[7]);
    void SaveOpenings(std::string openings[][7], int size);
    void ResetIDs(std::string openings[][7], int size);
    int StringToInt(std::string s);
    std::string IntToString(int i);
        void LoadOpenings(std::ifstream& infile);
   
};
#endif


// #ifndef OPENINGS_H
// #define OPENINGS_H

// #include <string>
// #include <fstream>

// class Openings {
// public:
//     Openings(int numOfOpenings);
//     Openings(std::string filename);
//     ~Openings();
//     void SetSize(int size);
//     int getSize();
//     void LoadOpenings(std::ifstream& infile);
//     void ResetIDs();
//     void PrintOpenings();
//     void AddOpening();
//     void DeleteOpening();
//     void swapOpenings(int indexA, int indexB);
//     void SaveOpenings();
//     std::string IntToString(int i);
//     int StringToInt(std::string s);

// private:
//     int num_of_openings;
//     std::string* (*openings)[7];
//     void GetOpening(std::string newOpening[]);
// };

// #endif // OPENINGS_H