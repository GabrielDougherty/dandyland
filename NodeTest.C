#include "Node.h"
//#include "Forest.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <cstdlib> // atexit
#include <algorithm>

using namespace std;

const char LINE[] = "------------------------------------";

vector<ptr> nodes;

void BuildTree(vector<ptr>& nodes, ifstream& inFile) {
	cout << endl << LINE << endl << "Building Tree" << endl;

	string line;
	// build an advance array
	while(getline(inFile, line)) {
		ptr tempPtr = new NodeT(AdvanceT(line));
		nodes.push_back(tempPtr);
	}

	// set up some dumb parent-child relationships
	for (size_t i = 0; i < nodes.size()-3; i +=3){
		nodes.at(i)->AddParent(nodes.at(i+1));
		nodes.at(i)->AddChild(nodes.at(i+2));
	}
}

void PrintNodes(const vector<ptr> nodes) {
	cout << endl << LINE << endl << "Printing tree" << endl;

	for (auto node : nodes) {
		cout << endl << "Node Name: " << node->Advance().Name()
			 << endl;

		cout << "Node Parents: " << endl;
		for (auto parent : node->Parents())
			cout << "\t" << parent->Advance().Name() << endl;

		cout << "Node Children: " << endl;
		for (auto child : node->Children())
			cout << "\t" << child->Advance().Name() << endl;
	}
}

void TestTree(const vector<ptr> nodes) {
	cout << endl << LINE << endl;
	cout << "Validating relationships in the tree, using"
		 << "\n\tIsChild(), IsParent(), Children(), Parents()" << endl;
	for (size_t i = 0; i < nodes.size()-3; i +=3){
		// Mirrors these calls:
		//     nodes.at(i)->AddParent(nodes.at(i+1));
		//     nodes.at(i)->AddChild(nodes.at(i+2));

		// this just verifies that values were set as expected
		// in BuildTree()
		assert(nodes.at(i)->IsChild(nodes.at(i+1)->Advance()));
		assert(nodes.at(i)->IsParent(nodes.at(i+2)->Advance()));



		// Do the same thing but manually going through Parents() and Children()

		// for Parents()

		// save other node's children
		const vector<ptr> otherChildren = nodes.at(i+1)->Children();
		const vector<ptr> parents = nodes.at(i)->Parents();

		// the other node should have this node as its child
		assert(find(otherChildren.cbegin(), otherChildren.cend(),
					nodes.at(i)) != otherChildren.end());
		// this node should have the other node as its parent
		assert(find(parents.cbegin(), parents.cend(),
					nodes.at(i+1)) != parents.cend());

		// for Children()

		// save other nodes' parents
		const vector<ptr> otherParents = nodes.at(i+2)->Parents();
		const vector<ptr> children = nodes.at(i)->Children();

		// the other node should have this node as its parent
		assert(find(otherParents.cbegin(), otherParents.cend(),
					nodes.at(i)) != otherParents.end());
		// this node should have the other node as its child
		assert(find(children.cbegin(), children.cend(),
					nodes.at(i+2)) != children.cend());

		cout << ".";
	}
	cout << "Sucess" << endl;
}

/*
void DeleteNodes(vector<ptr>& nodes) {
	for (auto node: nodes)
		delete node;
}
*/

int main() {

	cout << "NodeT Test" << endl << endl;

	ifstream inFile("Advance");

	BuildTree(nodes, inFile);

	// Just do DeleteNodes() but playing around with lambda expressions
	// (for fun)
	// This just deletes the dynamic memory
	atexit(
		   []() {
			   for (auto node : nodes)
				   delete node;
		   }
		);

	PrintNodes(nodes);

	TestTree(nodes);
	
	return 0;
}
