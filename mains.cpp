#include "openings.h"
#include <fstream>
#include <iostream>
#include "candidates.h"



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



    //Receives input from the user and performs appropriate command
//all operations require constant reading and writing of files
void Menu()
{   
    redo:
    int input;

    candidates candidateInstance;
    Openings openingsInstance1;

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
        openingsInstance1.AddOpening();

    else if(input == 2)
        openingsInstance1.DeleteOpening();

    else if(input == 3)
        openingsInstance1.PrintOpenings();
    else if(input == 4)
        FindMatches(candidateInstance.candidatearray, candidateInstance.num_of_candidates, openingsInstance1.openings, openingsInstance1.num_of_openings);

    else if(input == 5)
        candidateInstance.AddCandidate();

    else if(input == 6)
        candidateInstance.PrintCandidates();
    else if(input == 7)
        candidateInstance.ShowCandidatesByPosition();
    else if(input == 8)
        candidateInstance.FilterCandidatesByRating();
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


int main()
{
    Menu();
    return 0;
}