#include "candidates.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream> // for string streams
#include <stdlib.h>
#include <sys/stat.h>

using namespace std;

candidates::candidates()
{
    ifstream infile;
    num_of_candidates = 0;
    FileOpenFile(infile, "candidates.txt");
}

candidates::candidates(int numOfCandidates) : num_of_candidates(numOfCandidates)
{
    ifstream infile;
    num_of_candidates = numOfCandidates;

    FileOpenFile(infile, "candidates.txt");
}

candidates::candidates(string filename)
{
    ifstream infile;
    num_of_candidates = 0;
    FileOpenFile(infile, filename);
}

candidates::~candidates()
{
    delete[] candidatearray;
}

void candidates::candidates::SetSize(int size)
{

    this->num_of_candidates = size;
}

bool candidates::FileExists(const std::string &filename)
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void candidates::FileOpenFile(std::ifstream &infile, std::string filename)
{
    if (!FileExists(filename))
    {
        filename = GetFileName();
        FileOpenFile(infile, filename);
    }
    else
    {
        infile.open(filename, ios::in);
        infile >> num_of_candidates;
        candidatearray = new std::string[num_of_candidates][6];
        LoadCandidates(infile, candidatearray, num_of_candidates);
        infile.close();
    }
}

string candidates::GetFileName()
{
    cout << "Error: File not found. please enter the name of the file" << std::endl;
    string filename;
    cin >> filename;
    return filename;
}

int candidates::GetSize()
{
    return this->num_of_candidates;
}

// loads the contents of the candidates array in a 2D string array called candidates
// num candidates is the number of entries in the files, must be provided as a parameter
// meaning that thefile is opened at least ones before callign this function
void candidates::LoadCandidates(ifstream &infile, string candidates[][6], int num_candidates)
{
    // Loop through each candidate
    for (int i = 0; i < num_candidates; i++)
    {
        // Loop through each data field for current candidate
        for (int j = 0; j < 6; j++)
        {
            // Read data from file into array
            infile >> candidates[i][j];
        }
    }
}


void candidates::AddCandidate(){
    AddCandidate(candidatearray, num_of_candidates);
}
// adds a candidate to the candidates array
void candidates::AddCandidate(string candidates[][6], int size)
{
    string newCandidate[6];
    GetCandidate(newCandidate);
    string temp[size + 1][6];
    for (int i = 0; i < size; i++) // copy candidates to new structure
        for (int j = 0; j < 6; j++)
            temp[i][j] = candidates[i][j];

    for (int i = 0; i < 6; i++) // put new candidate at end of structure
    {
        temp[size][i] = newCandidate[i];
    }
    size++;
    SaveCandidates(temp, size); // save to file
}

void candidates::GetCandidate(string candidate[6])
{
    string temp;
    cout << endl
         << endl;
    cout << setw(25) << "Enter First Name:";
    cin >> temp;
    candidate[0] = temp;
    cout << setw(25) << "Enter Last Name:";
    cin >> temp;
    candidate[1] = temp;
    cout << setw(25) << "Enter Position:";
    cin >> temp;
    candidate[2] = temp;
    cout << setw(25) << "Enter Requested Salary:";
    cin >> temp;
    candidate[3] = temp;
    cout << setw(25) << "Enter Rating:";
    cin >> temp;
    candidate[4] = temp;
    cout << setw(25) << "Enter Phone Number:";
    cin >> temp;
    candidate[5] = temp;
}

void candidates::SaveCandidates(string temp[][6], int size)
{
    ofstream outfile;
    outfile.open("candidates.txt", ios::out);
    outfile << size << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 6; j++)
            outfile << setw(15) << left << temp[i][j];
        outfile << endl;
    }
    outfile.close();
}

void candidates::PrintCandidates(){
    PrintCandidates(candidatearray, num_of_candidates);
}

// prints all candidates in the candidates array
void candidates::PrintCandidates(string candidates[][6], int size)
{
    cout << setw(15) << "F. NAME:"
         << setw(15) << "L. NAME"
         << setw(15) << "POSITION"
         << setw(15) << "SALARY"
         << setw(15) << "RATING"
         << setw(15) << "PHO. #" << endl
         << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 6; j++)
            cout << setw(15) << std::left << candidates[i][j];
        cout << endl;
    }
    cout << endl
         << endl;
}


void candidates::ShowCandidatesByPosition(){
    ShowCandidatesByPosition(candidatearray, num_of_candidates);
}
// will prompt the user to enter an opening position
// will go though candidates and print anyone that matches
void candidates::ShowCandidatesByPosition(string candidates[][6], int size)
{
getPosition:
    cout << "Enter position:";
    string position;
    cin >> position;
    if (cin.fail() == true)
    {
        system("CLS");
        cout << "Invalid Input" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto getPosition;
    }

    cout << endl
         << endl;
    for (int i = 0; i < size; i++)
        if (candidates[i][2] == position)
        {
            for (int j = 0; j < 6; j++)
                cout << setw(15) << std::left << candidates[i][j];
            cout << endl;
        }
    cout << endl
         << endl;
}
void candidates::FilterCandidatesByRating(){
    FilterCandidatesByRating(candidatearray, num_of_candidates);
}

void candidates::FilterCandidatesByRating(string candidates[][6], int num_candidates)
{

    int rating;
    rating = 4;
    if (rating == 0)
    {
    GetRating:
        cout << "Enter minimum Rating(1-5): ";
        cin >> rating;

        if (cin.fail() == true || rating < 1 || rating > 5)
        {
            system("CLS");
            cout << "Invalid Input" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto GetRating;
        }
    }
    int qualified_indices[num_candidates][2];
    int counter = 0;

    // Step 2: Filling the 2D array
    for (int i = 0; i < num_candidates; i++)
    {
        int current_rating = StringToInt(candidates[i][4]);
        if (current_rating >= rating)
        {
            qualified_indices[counter][0] = i;              // storing index
            qualified_indices[counter][1] = current_rating; // storing rating
            counter++;
        }
    }
    // if theres only one item that meets the criteria we print it and return
    if (counter == 1)
    {
        PrintCandidate(candidates, static_cast<int>(qualified_indices[0][0]));
        return;
    }
    else if (counter == 0)
    {
        cout << "No candidates meet the criteria.\n";
        return;
    }

    // Step 3: Sorting the 2D array of qualified candidates by rating (ascending
    // use insertion sort because it is more efficient than bubble sort
    for (int i = 1; i < counter; i++)
    {
        int key[2] = {qualified_indices[i][0], qualified_indices[i][1]};
        int j = i - 1;

        while (j >= 0 && qualified_indices[j][1] > key[1])
        {
            qualified_indices[j + 1][0] = qualified_indices[j][0];
            qualified_indices[j + 1][1] = qualified_indices[j][1];
            j = j - 1;
        }
        qualified_indices[j + 1][0] = key[0]; // put the key row in the right place
        qualified_indices[j + 1][1] = key[1];
    }
    // Step 4 instead of allocating more memory to create another array of
    // candidates lets just use our sorted list  of indexs to print the candidates
    cout << setw(15) << "F. NAME:" << setw(15) << "L. NAME" << setw(15) << "POSITION" << setw(15) << "SALARY" << setw(15) << "RATING" << setw(15) << "PHO. #" << endl
         << endl;

    for (int i = 0; i < counter; i++)
    {
        int index = static_cast<int>(qualified_indices[i][0]);
        PrintCandidate(candidates, index);
    }
}

void candidates::PrintCandidate(string candidates[][6], int index)
{
    for (int j = 0; j < 6; j++)
        cout << setw(15) << std::left << candidates[index][j];
    cout << endl;
}

// given two row indexes in the openings array, swap their referenced rows with each other
void candidates::SwapCandidates(string candidates[][6], int indexA, int indexB)
{
    string temp;
    for (int j = 0; j < 6; j++)
    {
        temp = candidates[indexA][j];
        candidates[indexA][j] = candidates[indexB][j];
        candidates[indexB][j] = temp;
    }
}

int candidates::StringToInt(string s)
{
    stringstream temp(s);
    int integer = 0;
    temp >> integer;
    return integer;
}

// this converts integers to strings
string candidates::IntToString(int i)
{
    ostringstream str1;
    str1 << i;
    string temp = str1.str();
    return temp;
}