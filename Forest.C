#include "Forest.h"
#include <iostream>
#include <fstream>

using namespace std;

ForestT::ForestT(string filename) {
	// This is not done
	ifstream inFile(filename);

	string line;

	while (getline(inFile, line))
		AddAdvance(AdvanceT(line));
	FixAdvances();
}

void ForestT::AddAdvance(AdvanceT newAdvance) {
	if (FindAdvance(newAdvance.Name()) != nullptr)
		throw ADVANCE_ALREADY_EXISTS;

	ptr foundAdvance;
	ptr newNode;
	bool isChild = false;

	for (auto req : newAdvance.Requirements()) {
		foundAdvance = FindAdvance(req);
		if (foundAdvance != nullptr) {
			newNode = new NodeT(newAdvance);
			foundAdvance->AddChild(newNode);
			isChild = true;
		}
	}

	// if the node isn't a child of another node, it's just a
	// parent; add it to the list of nodes in the forest
	if (!isChild)
		advances.push_back(newNode);
}

ptr ForestT::FindAdvance(string advanceName) {
	ptr foundAdvance;
	for (auto tree : advances) {
		foundAdvance = DFS(tree, advanceName);
		if (foundAdvance != nullptr)
			return foundAdvance;
	}
	return nullptr;
}

ptr ForestT::DFS(ptr tree, string advanceName) {
	if (tree == nullptr)
		return nullptr;
	if (tree->Advance().Name() == advanceName)
		return tree;
	else
		for (auto child : tree->Children()) {
			ptr foundAdvance = DFS(child, advanceName);
			if (foundAdvance != nullptr)
				return foundAdvance;
		}
	return nullptr; //???maybe???
}

void ForestT::FixAdvances() {
	vector<ptr> toDelete; // vector of nodes to delete
	for (auto tree : advances) {
		if (tree->Requirements().size() > 0) {
			// need to delete it from forest
			toDelete.push_back(tree);
			for (auto req : tree->Requirements()) {
				FindAdvance(req)->AddChild(tree);
			}
		}
		FixParents(tree);
	}

	// remove nodes that have requirements from the forest
	for (auto tree : toDelete) {
		advances.erase(
					   find(advance.cbegin(), advance.cend(), tree)
					   );
	}

	for (auto tree : advances)
		FixParents(tree);
}

void FixParents(ptr tree) {
	for (auto req : tree->Requirements()) {
		ptr foundReq = FindAdvance(req);

		// if the node is not a child of the parent
		if (!foundReq->IsParent(tree))
			foundReq->AddChild(tree);
	}
	for (auto child : tree->Children())
		FixParents(child);
}
