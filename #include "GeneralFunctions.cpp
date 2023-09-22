#include "GeneralFunctions.h"
#include <fstream>
#include <iostream>

int main() {
    

    std::cout << "Openings instance created successfully.\n";
    
    Database openingsInstance(7,"openings.txt");

    openingsInstance.PrintDatabase(openingsInstance.general_database, openingsInstance.size_of_database);

    // openingsInstance.LoadOpenings(infile, openings, num_openings);
    // openingsInstance.PrintOpenings(openings, num_openings);
    // openingsInstance.AddOpening(openings, num_openings);
    // openingsInstance.PrintOpenings(openings, num_openings);
    return 0;