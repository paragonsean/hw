#include "GeneralFunctions.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>  // for string streams
#include <filesystem>
#include <stdlib.h>
#include <sys/stat.h>
#include "openings.h"
#include "candidates.h"

using namespace std;

#include <typeinfo>




Database::Database(int columns, string filename) {
    database_filename = filename;
    general_database = new string*[columns];
    ifstream infile;
    FileOpenFile(infile, database_filename, num_columns);
}

Database::Database(int size_of_database, int columns, string filename){
    general_database = new string*[7];
    ifstream infile;
    FileOpenFile(infile, database_filename, num_columns);
}



bool Database::FileExists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void Database::FileOpenFile(ifstream &infile, string filename, int columns) {
    num_columns = columns;
    if (!FileExists(filename)) {
        filename = GetFileName();
        FileOpenFile(infile, database_filename, columns);
    } else {
        infile.open(filename, ios::in);
        infile>>size_of_database;
        InitializeDatabase(size_of_database, num_columns);
        LoadDatabase(infile, general_database);
        infile.close();
    }
}


void Database::InitializeDatabase(int size, int columns) {
    size_of_database = size;
    for (int i = 0; i < size_of_database; ++i) {
        cout << "initializing database" << endl;
        general_database[i] = new string[num_columns];
    }
}

string Database::GetFileName(){
    cout << "Error: File not found. please enter the name of the file" << std::endl;
    string filename;
    cin >> filename;
    return filename;
}



void Database::LoadDatabase(ifstream &infile, string** general_database)
{   //reads a file and stores its contents in a 2D array
 
   for(int i=0; i<size_of_database; i++)
        for(int j=0; j<num_columns; j++)
        {
            infile>>general_database[i][j];
        }
}



void Database::PrintDatabase()
{
    PrintDatabase(this->general_database);
}

void Database::PrintDatabase(string** general_database)

    {
    cout<<setw(15)<<"ID"
        <<setw(15)<<"POSITION"
        <<setw(15)<<"DEPARTMENT"
        <<setw(15)<<"LEVEL"
        <<setw(15)<<"LOCATION"
        <<setw(15)<<"RELOCATION"
        <<setw(15)<<"EXPERIENCE"<<endl<<endl;
    for(int i=0; i<size_of_database; i++)
    {
        for(int j=0; j<7; j++)
            cout<<setw(15)<<std::left<<general_database[i][j];
        cout<<endl;
    }
    cout<<endl<<endl;
}


void Database::AddDatabase(){
    AddDatabase(this->general_database, this->size_of_database);
}
//allows the user to add an entry to the general_database array
//This function must invoke another function to get the generaldatabase
//then store it at the last place and store in the file, overwritting the old contents
void Database::AddDatabase(string** general_database, int size)
{   

     string newDatabase[num_columns];
     GetUserInput(newDatabase);
     resizeArray(general_database, size_of_database, size_of_database+1, num_columns);
    size_of_database++;
    for (int i=0; i<num_columns; i++){
     general_database[size_of_database][i] = newDatabase[i];
     
    }
    //  for (int i=0; i<size; i++)
    //     for (int j=0; j< size_of_database; j++){
    //         temp[i][j]=general_database[i][j];
    //     }
    
    //  for (int i=0; i<size_of_database; i++){
    //     temp[size][i] = newDatabase[i];
    //  }

    SaveDatabase(general_database, size_of_database);

}



//Used for general_database
void Database::SwapDatabase(string** general_database, int indexA, int indexB)
{
    string temp[num_columns];
    for (int i=0; i<size_of_database; i++){
        temp[i] = general_database[indexA][i];
        general_database[indexA][i] = general_database[indexB][i];
        general_database[indexB][i] = temp[i];
    }
}

void Database::GetUserInput(string *prompt)
{
    cout << "call from parent class";
}

void Database::SaveDatabase(string** general_database, int size)
{
    ofstream outfile;
    outfile.open(database_filename, ios::out); //opens the file for writing purposes
    outfile<<size<<endl;
    for(int i=0; i<size; i++)
    {
        for(int j=0; ; j++)
            outfile<<setw(15)<<left<<general_database[i][j];
        outfile<<endl;
    }
    outfile.close();
}


void Database::SetSize(int size){
    size_of_database = size;
}

int Database::GetSize(){
    return size_of_database;
}


