#include "openings.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>  // for string streams
#include <filesystem>
#include <stdlib.h>
#include <sys/stat.h>

using namespace std;


Openings::Openings(){
    ifstream infile;
    num_of_openings = 0;
    FileOpenFile(infile, "openings.txt");
}

Openings::Openings(int numOfOpenings): num_of_openings(numOfOpenings){
    ifstream infile;
    num_of_openings = numOfOpenings;

    FileOpenFile(infile, "openings.txt");
    
    }


Openings::Openings(string filename) { 
    ifstream infile;
    num_of_openings = 0;
    FileOpenFile(infile, filename);

}

Openings::~Openings(){
    delete[] openings;
}

void Openings::SetSize(int size){

    this->num_of_openings = size;

}

bool Openings::FileExists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void Openings::FileOpenFile(std::ifstream &infile, std::string filename) {
    if (!FileExists(filename)) {
        filename = GetFileName();
        FileOpenFile(infile, filename);
    } else {
        infile.open(filename, ios::in);
        infile>>num_of_openings;
        openings = new std::string[num_of_openings][7];
        LoadOpenings(infile, openings,num_of_openings);
        infile.close();
    }
}

string Openings::GetFileName(){
    cout << "Error: File not found. please enter the name of the file" << std::endl;
    string filename;
    cin >> filename;
    return filename;
}

int Openings::GetSize(){
    return this->num_of_openings;
}



void Openings::LoadOpenings(ifstream &infile, string openings[][7], int num_openings)
{   //reads a file and stores its contents in a 2D array
 
   for(int i=0; i<num_openings; i++)
        for(int j=0; j<7; j++)
        {
            infile>>openings[i][j];
        }
}


//This function rewrites the opening IDs.
//the first one gets 0, then 1, and so on.

void Openings::ResetIDs(string openings[][7], int size)
{
  for(int i=0; i<size; i++)
        openings[i][0]= IntToString(i); //everything is a string, need to convert it to do arithmetic operations
}


void Openings::PrintOpenings(){
    PrintOpenings(this->openings, this->num_of_openings);
}
void Openings::PrintOpenings(string openings[][7], int size)
{
    cout<<setw(15)<<"ID"
        <<setw(15)<<"POSITION"
        <<setw(15)<<"DEPARTMENT"
        <<setw(15)<<"LEVEL"
        <<setw(15)<<"LOCATION"
        <<setw(15)<<"RELOCATION"
        <<setw(15)<<"EXPERIENCE"<<endl<<endl;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<7; j++)
            cout<<setw(15)<<std::left<<openings[i][j];
        cout<<endl;
    }
    cout<<endl<<endl;
}

void Openings::AddOpening(){
    AddOpening(this->openings, this->num_of_openings);
}
//allows the user to add an entry to the openings array
//This function must invoke another function to get the opening
//then store it at the last place and store in the file, overwritting the old contents
void Openings::AddOpening(string openings[][7], int size)
{   
     
     string newOpening[7];
     GetOpening(newOpening);
     newOpening[0] = IntToString(size);
     string temp[size+1][7];
     for (int i=0; i<size; i++)
        for (int j=0; j<7; j++){
            temp[i][j]=openings[i][j];
        }
    
     for (int i=0; i<7; i++){
        temp[size][i] = newOpening[i];
     }
     size++;
    SaveOpenings(temp, size);

}



void Openings::DeleteOpening(){
    DeleteOpening(this->openings, this->num_of_openings);
}
/**
 * Deletes an opening from the 2D openings array by ID.
 * 
 * @param openings 2D array containing opening data
 * @param size Number of openings currently in the array
 * 
 * Prompts user for ID of opening to delete. Performs boundary check on ID.
 * If valid, swaps openings above deleted ID down to fill gap. 
 * Calls ResetIDs() to reorder remaining IDs.
 * Saves updated openings array with 1 less opening.
 */
void Openings::DeleteOpening(string openings[][7], int size)
{
     getId:
    cout<<"Enter ID of opening to delete(-1 to go back):";
    int del_id;
    cin>>del_id;
    if(cin.fail()==true || del_id < -1 || del_id > (size-1))
    {
        system("CLS");
        cout<<"Invalid Input"<<endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto getId;
    }
    if(del_id !=-1) //as long as ID inputted is not -1
    {
        int newSize = size-1;   //decrease the size
        for(int i=del_id; i<newSize; i++)
            SwapOpenings(openings, i, i+1); //and swap all elements above our deletion ID

        ResetIDs(openings, newSize);
        SaveOpenings(openings, newSize);//giving size-1 disregards the last element in the process, which has been swapped on the previous step
    }
    else
        system("CLS");

}



//Used for openings
void Openings::SwapOpenings(string openings[][7], int indexA, int indexB)
{
    string temp[7];
    for (int i=0; i<7; i++){
        temp[i] = openings[indexA][i];
        openings[indexA][i] = openings[indexB][i];
        openings[indexB][i] = temp[i];
    }
}

void Openings::GetOpening(string opening[7])
{
    string temp;    //we keep re-assining values to this temp variable
    cout<<endl<<endl;
    cout<<setw(25)<<"Enter Position Title:";
    cin>>temp;
    opening[1]=temp;    //store temp value to its place in the array
    cout<<setw(21)<<"Enter Department:";
    cin>>temp;
    opening[2]=temp;
    cout<<setw(21)<<"Enter Level(1-3):";
    cin>>temp;
    opening[3]=temp;
    cout<<setw(39)<<"Enter Location(state abbreviation):";
    cin>>temp;
    opening[4]=temp;
    cout<<setw(38)<<"Enter Relocation Benefits(yes/no):";
    cin>>temp;
    opening[5]=temp;
    cout<<setw(45)<<"Enter Experience requirement(# of years):";
    cin>>temp;
    opening[6]=temp;
}

void Openings::SaveOpenings(string openings[][7], int size)
{
    ofstream outfile;
    outfile.open("openings-1.txt", ios::out); //opens the file for writing purposes
    outfile<<size<<endl;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<7; j++)
            outfile<<setw(15)<<left<<openings[i][j];
        outfile<<endl;
    }
    outfile.close();
}

std::string Openings::IntToString(int i)
{
    std::ostringstream str1;
    str1<<i;
    std::string temp = str1.str();
    return temp;
}

int Openings::StringToInt(std::string s)
{
    std::stringstream temp(s);
    int integer = 0;
    temp >> integer;
    return integer;
}