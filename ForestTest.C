#include "Forest.h"
#include "Node.h"
#include "NodeTestUtils.h"
#include <iostream>
#include <assert.h>

using namespace std;

// this is a global variable because I delete the data in atexit(),
// which takes a function pointer, and function pointers can't take// parameters
std::vector<ptr> nodes;

/*
class ForestTesterT : public ForestT {
public:
	ForestTesterT(string filename) : ForestT(filename);

	
};
*/

void TestAdvanceExists(const vector<ptr>& nodes,
					   const ForestT& forest) {
	cout << endl << NodeTestUtils::LINE << endl << "Testing AdvanceExists()"
		 << endl;
	for (auto node : nodes)
		assert(forest.AdvanceExists(node->Advance().Name()));
	cout << "Success" << endl;
}

int main() {
	// build a vector of advances with which to compare the
	// forest to
	ifstream inFile("Advance");

	atexit(NodeTestUtils::DeleteNodes);
	NodeTestUtils::ReadTreeFile(nodes, inFile);
	
	ForestT forest("Advance");

	TestAdvanceExists(nodes, forest);

	forest.PrintAll();
	return 0;
}
