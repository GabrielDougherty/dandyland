#include "NodeTestUtils.h"

using namespace NodeTestUtils;
using namespace std;

// this is a global variable because I delete the data in atexit(),
// which takes a function pointer, and function pointers can't take// parameters
std::vector<ptr> nodes;

int main() {

	cout << "NodeT Test" << endl << endl;

	ifstream inFile("Advance");

	ReadTreeFile(nodes, inFile);
	BuildTree(nodes);

	// Just do DeleteNodes() but playing around with lambda expressions
	// (for fun)
	// This just deletes the dynamic memory in the array
	atexit(DeleteNodes);

	PrintNodes(nodes);

	TestTree(nodes);
	
	return 0;
}
