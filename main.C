#include <iostream>
#include "Advance.h"
#include "Node.h"
#include "Forest.h"

using namespace std;

void Explore(const ForestT & advances);

int main() {
    ForestT advances; 

    cout << "Loaded advances: " << endl;
    advances.PrintAll();

    Explore(advances);
    return 0;
}

void Explore(const ForestT & advances){
    string line;

    cout <<"Enter an advance to explore => ";
    getline(cin,line);
    while (line != "QUIT") {
        if (advances.AdvanceExists(line)) {

	   cout << "****************" << endl;
	   cout << "A " << line << " is needed to build: " << endl;
	   advances.PrintChildren(line);
	   cout << "****************" << endl;

	   cout << "To build a " <<line << " the following are needed " << endl;
	   advances.PrintParents(line);
	   cout << endl << endl;

	} else {
	   cout << line << " is not in the advance list " << endl;
	}

        cout <<"Enter an advance to explore => ";
        getline(cin,line);
    }

    return;
}
