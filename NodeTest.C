#include "Node.h"
//#include "Forest.h"
#include <iostream>
#include <fstream>


using namespace std;

void BuildNodes(vector<NodeT>& nodes, ifstream& inFile) {
	string line;
	// build an advance array
	while(getline(inFile, line)) {
		nodes.push_back(NodeT(AdvanceT(line)));
	}

	// set up some dumb parent-child relationships
	for (size_t i = 0; i < nodes.size()-3; i +=3){
		nodes.at(i).AddParent(&nodes.at(i+1));
		nodes.at(i).AddChild(&nodes.at(i+2));
	}
}

void PrintNodes(vector<NodeT> nodes) {
	for (auto node : nodes) {
		cout << endl << "Node Name: " << node.Advance().Name()
			 << endl;
		cout << "Node Parents: " << endl;
		for (auto parent : node.Parents())
			cout << "\t" << parent->Advance().Name() << endl;
		cout << "Node Children: " << endl;
		for (auto child : node.Children())
			cout << "\t" << child->Advance().Name() << endl;
		
	}
}

int main() {
	vector<NodeT> nodes;

	cout << "TESTING NODES" << endl;

	ifstream inFile("Advance");
	BuildNodes(nodes, inFile);
	PrintNodes(nodes);
	
	return 0;
}
