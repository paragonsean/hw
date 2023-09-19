#include "Candidates.h"
#include <sstream>

using namespace std;

Candidates::Candidates() {
    // Constructor implementation (if needed)
}

// Read in the candidates from the file
void Candidates::loadCandidates(std::ifstream& infile, std::string candidates[][6], int num_candidates) {
    // Loop through each row of the array
    for (int i = 0; i < num_candidates; i++)
        // Loop through each column of the current row
        for (int j = 0; j < 6; j++) {
            // Read in the candidate's data from the file
            infile >> candidates[i][j];
        }
}



/*
 * This function adds a new candidate to the candidates array.
 * The new candidate is entered by the user.
 * The new candidate is added to the end of the array.
 * The array is then saved to the candidates file.
 */

void Candidates::AddCandidate(string candidates[][6], int size)
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




void Candidates::GetCandidate(string candidate[6])
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

void Candidates::SaveCandidates(string temp[][6], int size)
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

void Candidates::PrintCandidates(string candidates[][6], int size)
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
void Candidates::ShowCandidatesByPosition(string candidates[][6], int size)
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
void Candidates::SortByRating(string candidates[][6], int num_candidates)
{
   for (int i = 0; i < num_candidates; i++)
       for (int j = 0; j < num_candidates-i-1; j++)
           if (candidates[j][4] > candidates[j+1][4])
              SwapCandidates(candidates, j, j+1);
    PrintCandidates(candidates, num_candidates);
}




void Candidates::FilterCandidatesByRating(string candidates[][6], int num_candidates)
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

void Candidates::PrintCandidate(string candidates[][6], int index)
{
    for(int j=0; j<6; j++)
        cout<<setw(15)<<std::left<<candidates[index][j];
    cout<<endl;
}
