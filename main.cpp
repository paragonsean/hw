#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>  // for string streams
#include <stdlib.h>

using namespace std;

void Menu();
string IntToString(int i);
int StringToInt(string s);
void AddOpening(string openings[][7], int size);
void PrintOpenings(string openings[][7], int size);
void LoadOpenings(ifstream& infile, string openings[][7], int num_openings);
void DeleteOpening(string openings[][7], int size);
void GetOpening(string opening[7]);
void SaveOpenings(string openings[][7], int size);
void ResetIDs(string openings[][7], int size);
void swapItems(string openings[][7], int indexA, int indexB);
void FindMatches(string candidates[][6], int cand_size, string openings[][7], int opening_size);
void GetCandidate(string candidate[6]);
void SaveCandidates(string temp[][6], int size);
void LoadCandidates(ifstream& infile, string candidates[][6], int num_candidates);
void AddCandidate(string candidates[][6], int size);
void ShowCandidatesByPosition(string candidates[][6], int size);
void PrintCandidates(string candidates[][6], int size);
void SwapCandidates(string candidates[][6], int indexA, int indexB);
void SortByRating(string candidates[][6], int num_candidates);
void FilterCandidatesByRating(string candidates[][6], int num_candidates);
void PrintCandidate(string temp[][6], int index);

int main()
{
    Menu();
    return 0;
}


//loads the contents of the candidates array in a 2D string array called candidates
//num candidates is the number of entries in the files, must be provided as a parameter
//meaning that thefile is opened at least ones before callign this function
void LoadCandidates(ifstream& infile, string candidates[][6], int num_candidates)
{
    // Loop through each candidate
    for (int i=0; i<num_candidates; i++) {
        // Loop through each data field for current candidate
        for(int j=0; j<6; j++) {
            // Read data from file into array
            infile >> candidates[i][j];
        }
    }
}
void AddCandidate(string candidates[][6], int size)
{
    string newCandidate[6];
    GetCandidate(newCandidate);
    string temp[size+1][6];
    for(int i=0; i<size; i++)   //copy candidates to new structure
        for(int j=0; j<6; j++)
            temp[i][j]=candidates[i][j];

    for(int i=0; i<6; i++)  //put new candidate at end of structure
    {
        temp[size][i]=newCandidate[i];
    }
    size++;
    SaveCandidates(temp, size); //save to file
}

void GetCandidate(string candidate[6])
{
    string temp;
    cout<<endl<<endl;
    cout<<setw(25)<<"Enter First Name:";
    cin>>temp;
    candidate[0]=temp;
    cout<<setw(25)<<"Enter Last Name:";
    cin>>temp;
    candidate[1]=temp;
    cout<<setw(25)<<"Enter Position:";
    cin>>temp;
    candidate[2]=temp;
    cout<<setw(25)<<"Enter Requested Salary:";
    cin>>temp;
    candidate[3]=temp;
    cout<<setw(25)<<"Enter Rating:";
    cin>>temp;
    candidate[4]=temp;
    cout<<setw(25)<<"Enter Phone Number:";
    cin>>temp;
    candidate[5]=temp;
}

void SaveCandidates(string temp[][6], int size)
{
     ofstream outfile;
    outfile.open("candidates.txt", ios::out);
    outfile<<size<<endl;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<6; j++)
            outfile<<setw(15)<<left<<temp[i][j];
        outfile<<endl;
    }
    outfile.close();
}

void PrintCandidates(string candidates[][6], int size)
{
        cout<<setw(15)<<"F. NAME:"
            <<setw(15)<<"L. NAME"
            <<setw(15)<<"POSITION"
            <<setw(15)<<"SALARY"
            <<setw(15)<<"RATING"
            <<setw(15)<<"PHO. #"<<endl<<endl;
        for(int i=0; i<size; i++)
        {
            for(int j=0; j<6; j++)
                cout<<setw(15)<<std::left<<candidates[i][j];
        cout<<endl;
        }
        cout<<endl<<endl;
}
//will prompt the user to enter an opening position
//will go though candidates and print anyone that matches
void ShowCandidatesByPosition(string candidates[][6], int size)
{
    getPosition:
        cout<<"Enter position:";
        string position;
        cin>>position;
        if(cin.fail()==true)
        {
            system("CLS");
            cout<<"Invalid Input"<<endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto getPosition;
        }

    cout<<endl<<endl;
    for(int i=0; i<size; i++)
        if(candidates[i][2]==position)
        {
            for(int j=0; j<6; j++)
                cout<<setw(15)<<std::left<<candidates[i][j];
            cout<<endl;
        }
    cout<<endl<<endl;
}

//We must sort the candidates array based on the rating value
void SortByRating(string candidates[][6], int num_candidates)
{
   for (int i = 0; i < num_candidates; i++)
       for (int j = 0; j < num_candidates-i-1; j++)
           if (candidates[j][4] > candidates[j+1][4])
              SwapCandidates(candidates, j, j+1);
    PrintCandidates(candidates, num_candidates);
}




void FilterCandidatesByRating(string candidates[][6], int num_candidates)
{
    int rating;
    GetRating:
    cout<<"Enter minimum Rating(1-5): ";
    cin>>rating;

    if(cin.fail() == true || rating<1 || rating > 5)
    {
        system("CLS");
        cout<<"Invalid Input"<<endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto GetRating;
    }

    int counter=0;
    string temp;
    for(int i=0; i<num_candidates; i++)
    {
        temp = candidates[i][4];
        if(StringToInt(temp)>= rating)
            counter++;
    }
    string f_cand[counter][6];
    int copied=0;
    while(copied<counter)
    {
        for(int i=0; i<num_candidates; i++)
        {
            temp = candidates[i][4];
            if(StringToInt(temp)>= rating)
            {
                for(int k=0; k<6; k++){
                    f_cand[copied][k]=candidates[i][k];
                    if (counter == 1){
                        PrintCandidate(candidates, i);
                        return;
                    }
                }
                copied++;
            }
        }
    }
    SortByRating(f_cand, counter);
}

void PrintCandidate(string candidates[][6], int index)
{
    for(int j=0; j<6; j++)
        cout<<setw(15)<<std::left<<candidates[index][j];
    cout<<endl;
}


//This function rewrites the opening IDs.
//the first one gets 0, then 1, and so on.
void ResetIDs(string openings[][7], int size)
{
  for(int i=0; i<size; i++)
        openings[i][0]= IntToString(i); //everything is a string, need to convert it to do arithmetic operations
}

void LoadOpenings(ifstream& infile, string openings[][7], int num_openings)
{   //reads a file and stores its contents in a 2D array
   for(int i=0; i<num_openings; i++)
        for(int j=0; j<7; j++)
        {
            infile>>openings[i][j];
        }
}

void PrintOpenings(string openings[][7], int size)
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
//allows the user to add an entry to the openings array
//This function must invoke another function to get the opening
//then store it at the last place and store in the file, overwritting the old contents
void AddOpening(string openings[][7], int size)
{   
    
     string newOpening[7];
     GetOpening(newOpening);
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

void DeleteOpening(string openings[][7], int size)
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
            swapItems(openings, i, i+1); //and swap all elements above our deletion ID

        ResetIDs(openings, newSize);
        SaveOpenings(openings, newSize);//giving size-1 disregards the last element in the process, which has been swapped on the previous step
    }
    else
        system("CLS");

}

//Used for openings
void swapItems(string openings[][7], int indexA, int indexB)
{
    string temp[7];
    for (int i=0; i<7; i++){
        temp[i] = openings[indexA][i];
        openings[indexA][i] = openings[indexB][i];
        openings[indexB][i] = temp[i];
    }
}

void GetOpening(string opening[7])
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

void SaveOpenings(string openings[][7], int size)
{
    ofstream outfile;
    outfile.open("openings.txt", ios::out); //opens the file for writing purposes
    outfile<<size<<endl;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<7; j++)
            outfile<<setw(15)<<left<<openings[i][j];
        outfile<<endl;
    }
    outfile.close();
}
//given two row indexes in the openings array, swap their referenced rows with each other
void SwapCandidates(string candidates[][6], int indexA, int indexB)
{
    string temp;
    for(int j = 0; j<6;j++)
    {
        temp = candidates[indexA][j];
        candidates[indexA][j]=candidates[indexB][j];
        candidates[indexB][j]=temp;
    }
}
//Find all candidates that match any opening and print them
void FindMatches(string candidates[][6], int cand_size, string openings[][7], int opening_size)
{
    for(int i=0; i<opening_size; i++)
    {
        cout<<endl<<endl;
        cout<<"Candidates for opening "<<openings[i][1]<<endl;
        cout<<setw(15)<<"F. NAME:"
            <<setw(15)<<"L. NAME"
            <<setw(15)<<"POSITION"
            <<setw(15)<<"SALARY"
            <<setw(15)<<"RATING"
            <<setw(15)<<"PHO. #"<<endl<<endl;
        for(int j=0; j<cand_size; j++)
        {
            if(candidates[j][2]==openings[i][1])
            {
                for(int k=0; k<6; k++)
                    cout<<setw(15)<<std::left<<candidates[j][k];
                cout<<endl;
            }
        }
    }
    cout<<endl<<endl;
}

int StringToInt(string s)
{
    stringstream temp(s);
    int integer = 0;
    temp >> integer;
    return integer;
}

//this converts integers to strings
string IntToString(int i)
{
    ostringstream str1;
    str1<<i;
    string temp = str1.str();
    return temp;
}



//Receives input from the user and performs appropriate command
//all operations require constant reading and writing of files
void Menu()
{
    int input;

    ifstream inOpenings;    //this variable will allow input operations for the openings file
    int num_openings;
    ifstream inCandidates;  //this variable will allow input operations for the candidates file
    int num_candidates;

    redo:
    //we need to load every time
    inOpenings.open("openings.txt", ios::in);   //open files
    inOpenings>>num_openings;                   //read # of entries in file
    inCandidates.open("candidates.txt", ios::in);
    inCandidates>>num_candidates;

    string openings[num_openings][7];       //create array to store info currently in file
    string candidates[num_candidates][6];
    LoadOpenings(inOpenings, openings, num_openings);   //this loads the contents to the array, so that we can use it in subsequent operations
    LoadCandidates(inCandidates, candidates, num_candidates);
    inOpenings.close(); //close the files
    inCandidates.close();

    GetSelection:          //This is a label, a destination for a goto statement. Allows us to reenter the menu without writing a while loop

    cout<<"1.   "<<setw(40)<<std::left<<"Add Opening"<<endl;
    cout<<"2.   "<<setw(40)<<std::left<<"Delete Opening"<<endl;
    cout<<"3.   "<<setw(40)<<std::left<<"Show Openings"<<endl;
    cout<<"4.   "<<setw(40)<<std::left<<"Match Candidates to all Openings"<<endl<<endl;

    cout<<"5.   "<<setw(40)<<std::left<<"Add Candidate"<<endl;
    cout<<"6.   "<<setw(40)<<std::left<<"Show Candidates"<<endl;
    cout<<"7.   "<<setw(40)<<std::left<<"Show Candidates by position"<<endl;
    cout<<"8.   "<<setw(40)<<std::left<<"Filter Candidates By Rating"<<endl<<endl;

    cout<<"9.   "<<setw(40)<<std::left<<"Clear Screen"<<endl;
    cout<<"Enter Selection:";
    cin>>input;

    if(cin.fail() == true || input>9)
    {
        system("CLS");
        cout<<endl<<endl;
        cout<<"Invalid Input. Please Re-enter Selection"<<endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto GetSelection;
    }
    else if(input == 1)
        AddOpening(openings, num_openings);

    else if(input == 2)
        DeleteOpening(openings, num_openings);

    else if(input == 3)
        PrintOpenings(openings, num_openings);
    else if(input == 4)
        FindMatches(candidates, num_candidates, openings, num_openings);

    else if(input == 5)
        AddCandidate(candidates, num_candidates);

    else if(input == 6)
        PrintCandidates(candidates,  num_candidates);
    else if(input == 7)
        ShowCandidatesByPosition(candidates, num_candidates);
    else if(input == 8)
        FilterCandidatesByRating(candidates, num_candidates);
    else if(input == 9)
    {
        system("CLS");
    }
    else
        goto end;
    goto redo;
    end:
    cout<<endl<<endl;
    cout<<"Termination"<<endl;
}

