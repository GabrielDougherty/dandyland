#include "Forest.h"
#include <iostream>
#include <fstream>

using namespace std;

ForestT::ForestT(string filename) {
	// This is not done probably maybe
	ifstream inFile(filename);

	string line;

	while (getline(inFile, line))
		AddAdvance(AdvanceT(line));

	FixAdvances();
}

ForestT::~ForestT() {
	cout << "ENTERING DESTRUCTOR" << endl;

	vector<ptr> killList;
	for (auto tree : advances)
		KillTree(tree, killList);

	cout << "KILLLIST LENGTH" << killList.size() << endl;
	
	// DEBUG: print killList
	for (auto it : killList)
		cout << "\t KILLING " << it->Advance().Name() << endl;
	
	for (auto tree : killList)
		delete tree;
}

void ForestT::AddAdvance(AdvanceT newAdvance) {
	if (FindAdvance(newAdvance.Name()) != nullptr)
		throw ADVANCE_ALREADY_EXISTS;

	ptr foundAdvance;
	ptr newNode = new NodeT(newAdvance);
	bool isChild = false;

	for (string req : newAdvance.Requirements()) {
		foundAdvance = FindAdvance(req);
		if (foundAdvance != nullptr) {
			foundAdvance->AddChild(newNode);
			isChild = true;
		}
	}

	// if the node isn't a child of another node, it's just a
	// parent; add it to the list of nodes in the forest
	if (!isChild)
		advances.push_back(newNode);
}

ptr ForestT::FindAdvance(string advanceName) const {
	ptr foundAdvance;
	for (auto tree : advances) {
		foundAdvance = DFS(tree, advanceName);
		if (foundAdvance != nullptr)
			return foundAdvance;
	}
	return nullptr;
}

ptr ForestT::DFS(ptr tree, string advanceName) const {
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
	// credit to Dr. Bennett for most of this algorithm

	auto it = advances.cbegin();
	while (it != advances.cend()) {
		if ((*it)->Advance().Requirements().size() > 0) {
			// need to delete it from forest
			ptr data = *it;
			it = advances.erase(it);
			for (auto req : data->Advance().Requirements()) {
				FindAdvance(req)->AddChild(data);
			}
		}
		else
			it++;
	}

	// fix all the nodes in the forest
	for (auto tree : advances)
		FixParents(tree);
}

void ForestT::FixParents(ptr tree) {
	for (auto req : tree->Advance().Requirements()) {
		ptr foundReq = FindAdvance(req);

		// if the node is not a child of the parent
		if (!foundReq->IsParent(tree->Advance()))
			foundReq->AddChild(tree);
	}
	for (auto child : tree->Children())
		FixParents(child);
}

void ForestT::KillTree(ptr tree, vector<ptr>& killList) {
	auto it = find(killList.cbegin(), killList.cend(), tree);

	if (it == killList.cend())
		killList.push_back(tree);

	for (ptr child : tree->Children())
		KillTree(child, killList);
}

bool ForestT::AdvanceExists(string advanceName) const {
	for (auto tree : advances)
		if (DFS(tree, advanceName) != nullptr)
			return true;
	return false;
}

void ForestT::PrintParents(string advanceName) const {
	ptr foundAdvance = FindAdvance(advanceName);

	DFSPrint(foundAdvance, 0, DirectionT::UP);
}

void ForestT::PrintChildren(string advanceName) const {
	ptr foundAdvance = FindAdvance(advanceName);

	DFSPrint(foundAdvance, 0, DirectionT::DOWN);
}

void ForestT::PrintAll() const {
	for (auto tree : advances) {
		PrintChildren(tree->Advance().Name());
	}
}

void ForestT::DFSPrint(ptr tree, int depth,
					   DirectionT direction) const {
	// print depth tabs
	for (int i = 0; i < depth; i++)
		cout << "\t";

	cout << tree->Advance().Name() << endl;

	switch (direction) {
	case DirectionT::UP:
		for (auto parent : tree->Parents())
			DFSPrint(parent, depth+1, DirectionT::UP);
	case DirectionT::DOWN:
		for (auto child : tree->Children())
			DFSPrint(child, depth+1, DirectionT::DOWN);
	}
}
