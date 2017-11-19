#include "NodeTester.h"

using namespace std;


// This does not work
// NodeTester::NodeTester(const string filename) : ReadFile(filename), BuildTree() {}

NodeTester::NodeTester(const string filename) {
	// These didn't work in an initializer list...
	ReadFile(filename);
	BuildTree();
}

NodeTester::~NodeTester() {
	for (auto node: nodes)
		delete node;
}

void NodeTester::ReadFile(string filename) {
	ifstream inFile(filename);
	string line;
	// build an advance array
	while(getline(inFile, line)) {
		ptr tempPtr = new NodeT(AdvanceT(line));
		nodes.push_back(tempPtr);
	}
}

void NodeTester::BuildTree() {
	cout << endl << LINE << endl << "Building Node Relationship List" << endl;
	
	// set up some dumb parent-child relationships
	// i          i+1          i+2
	// |           |            |
	// child of----+            |
	// parent of----------------+
	//
	// for array:
	// [ i | i+1 | i+2 | i | i+1 | ... ]
	//
	
	for (size_t i = 0; i < nodes.size()-3; i +=3){
		nodes.at(i)->AddParent(nodes.at(i+1));
		nodes.at(i)->AddChild(nodes.at(i+2));
	}
}

void NodeTester::PrintNodes() const {
	cout << endl << LINE << endl << "Printing Node Relationships" << endl;

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

// tests ForestT::IsChild()
void NodeTester::TestIsChild(const int i) const {
	// the node should be a child of the i+1th node
	assert(nodes.at(i)->IsChild(nodes.at(i+1)->Advance()));

	// the node should not be a child of Bob the Builder
	assert(!nodes.at(i)->IsChild(AdvanceT("Bob the Builder,-,Yes We Can")));
}

// tests ForestT::IsParent()
void NodeTester::TestIsParent(const int i) const {
	// the node should be a parent of the i+2th node
	assert(nodes.at(i)->IsParent(nodes.at(i+2)->Advance()));

	// the node should not be a parent of Bob the Builder
	assert(!nodes.at(i)->IsParent(AdvanceT("Bob the Builder,-,Yes We Can")));
}

// tests ForestT::Parents()
void NodeTester::TestParents(const int i) const {
	// Make a Bob the Builder node
	NodeT bobTheBuilder(AdvanceT("Bob the Builder,-,Yes We Can"));

	// save other node's children
	const vector<ptr> otherChildren = nodes.at(i+1)->Children();
	const vector<ptr> parents = nodes.at(i)->Parents();

	// the other node should have this node as its child
	assert(find(otherChildren.cbegin(), otherChildren.cend(),
				nodes.at(i)) != otherChildren.end());
	// the other node should not have Bob the Builder as its child
	assert(find(otherChildren.cbegin(), otherChildren.cend(),
				&bobTheBuilder) == otherChildren.cend());
	
	// this node should have the other node as its parent
	assert(find(parents.cbegin(), parents.cend(),
				nodes.at(i+1)) != parents.cend());
	// this node should not have Bob the Builder as its parent
	assert(find(parents.cbegin(), parents.cend(),
				&bobTheBuilder) == parents.cend());

}

// tests ForestT::Children()
void NodeTester::TestChildren(const int i) const {
	// Make a Bob the Builder node
	NodeT bobTheBuilder(AdvanceT("Bob the Builder,-,Yes We Can"));

	// save other nodes' parents
	const vector<ptr> otherParents = nodes.at(i+2)->Parents();
	const vector<ptr> children = nodes.at(i)->Children();

	// the other node should have this node as its parent
	assert(find(otherParents.cbegin(), otherParents.cend(),
				nodes.at(i)) != otherParents.end());
	// the other node should not have Bob the Builder as its parent
	assert(find(otherParents.cbegin(), otherParents.cend(),
				&bobTheBuilder) == otherParents.end());
	
	// this node should have the other node as its child
	assert(find(children.cbegin(), children.cend(),
				nodes.at(i+2)) != children.cend());
	// this node should not have Bob the Builder as its child
	assert(find(children.cbegin(), children.cend(),
				&bobTheBuilder) == children.cend());

}

void NodeTester::RunAllTests() const {
	cout << endl << LINE << endl;
	cout << "Validating relationships in the tree, using"
		 << "\n\tIsChild(), IsParent(), Children(), Parents()" << endl;
	for (size_t i = 0; i < nodes.size()-3; i +=3){
		// Mirrors these calls from BuildTree():
		//     nodes.at(i)->AddParent(nodes.at(i+1));
		//     nodes.at(i)->AddChild(nodes.at(i+2));

		// this just verifies that values were set as expected
		TestIsChild(i);
		TestIsParent(i);

		// Do the same thing but manually going through Parents() and Children()
		// for Parents()
		TestParents(i);
		// for Children()
		TestChildren(i);
		cout << ".";
	}
	cout << "Sucess" << endl;
}

vector<ptr> NodeTester::Nodes() const {
	return nodes;
}
