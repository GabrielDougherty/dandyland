// ForestTest.C
// Gabriel Dougherty

#include "Forest.h"
#include "Node.h"
#include "NodeTester.h"
#include <iostream>
#include <assert.h>

const char * LINE = "------------------------------------------";

using namespace std;
/*
class ForestTesterT : public ForestT {
public:
	ForestTesterT(string filename) : ForestT(filename);

	
};
*/

void TestAdvanceExists(const vector<ptr> nodes,
					   const ForestT& forest) {
	cout << endl << LINE << endl << "Testing AdvanceExists()"
		 << endl;
	for (auto node : nodes) {
		assert(forest.AdvanceExists(node->Advance().Name()));
		cout << ".";
	}
	assert(!forest.AdvanceExists("Bob the Builder"));
	cout << "Success" << endl;
}

void PrintForest(const ForestT& forest) {
	cout << endl << LINE << endl << "Printing Forest" << endl
		 << LINE << endl;

	forest.PrintAll();
}	

void TestAdvanceAlreadyExists() {
	cout << endl << LINE << endl << "Testing ADVANCE_ALREADY_EXISTS error in AddAdvance()" << endl
		 << LINE << endl;

	try {
		ForestT badForest("BadAdvance");
	} catch (int error) {
		if (error == 1)
			cerr << "Caught ADVANCE_ALREADY_EXISTS; test Success" << endl;
		else
			cerr << "Unknown error caught: " << error << "; test Failed" << endl;
	}
}

int main() {
	// Build a list of nodes from "Advance"
	NodeTester tester;

	ForestT forest;

	cout << endl << LINE << endl
		 << "Running ForestT Tests" << endl;
	
	TestAdvanceExists(tester.Nodes(), forest);

		
	PrintForest(forest);

	TestAdvanceAlreadyExists();


	return 0;
}
