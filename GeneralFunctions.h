#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include <typeinfo>
 #include <string>
 

class Database {
private:
    // std::string** general_database;
    
    // int size_of_database;
    // int num_columns;  // Add this if the number of columns can change
    // std::string database_filename;

public:

    std::string** general_database;

    int size_of_database;
    int num_columns;  // Add this if the number of columns can change
    std::string database_filename;

    std::string headers[];
    Database();
    Database(int columns);
     Database(int size_of_datase, int columns);
    Database(int size_of_database, int columns, std::string filename);
    Database(int columns, std::string filename);
    // ~Database();

    bool FileExists(const std::string& filename);
    void FileOpenFile(std::ifstream& infile, std::string filename, int columns);
    void InitializeDatabase(int size,int columns);
    std::string GetFileName();
    void GetUserInput(std::string* prompt);
    void LoadDatabase(std::ifstream& infile, std::string** general_database);
    void PrintDatabase();
    virtual void PrintDatabase(std::string** general_database);
    void AddDatabase();
    void AddDatabase(std::string** general_database, int size);
        void SwapDatabase(std::string** general_database, int indexA, int indexB);
    virtual void GetDatabase(std::string generaldatabase[]);
    void SaveDatabase(std::string** general_database, int size);
    std::string IntToString(int i);
    int StringToInt(std::string s);
    void GetDatabase();
    // std::string** resizeArray(std::string** original, int oldSize, int newSize, int constSize); 

    void SetSize(int size);
    int GetSize();
    };
#endif