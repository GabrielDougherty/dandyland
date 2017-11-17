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
	vector<ptr> killList;
	for (auto tree : advances)
		KillTree(tree, killList);
	for (auto tree : killList)
		delete tree;
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
		if (tree->Advance().Requirements().size() > 0) {
			// need to delete it from forest
			toDelete.push_back(tree);
			for (auto req : tree->Advance().Requirements()) {
				FindAdvance(req)->AddChild(tree);
			}
		}
		FixParents(tree);
	}

	// remove nodes that have requirements from the forest
	for (auto tree : toDelete) {

		advances.erase(/*find thing to erase*/);
		// advances.erase( // PLAYING WITH LAMBDA EXPRESSIONS
		// 			   [tree, adv = this->advances]() -> vector<ptr>::const_iterator{
		// 				   vector<ptr>::const_iterator it;
		// 				   for (it = adv.cbegin(); it != adv.cend(); it++)
		// 					   if (*it == tree)
		// 						   return it;
		// 				   return it;
		// 			   }
		// 			   );
	}

	for (auto tree : advances)
		FixParents(tree);
}

void FixParents(ptr tree) {
	for (auto req : tree->Advance().Requirements()) {
		ptr foundReq = FindAdvance(req);

		// if the node is not a child of the parent
		if (!foundReq->IsParent(tree))
			foundReq->AddChild(tree);
	}
	for (auto child : tree->Children())
		FixParents(child);
}

void KillTree(ptr tree, vector<ptr> killList) {
	auto it = find(killList.cbegin(), killList.cend(), tree);

	if (it != killList.cend())
		killList.push_back(tree);

	for (auto child : tree->Children()) {
		KillTree(child, killList);
	}
}

bool AdvanceExists(string advanceName) {
	for (auto tree : advances)
		if (DFS(tree, advanceName) != nullptr)
			return true;
	return false;
}

void PrintParents(string advanceName) {
	ptr foundAdvance = FindAdvance(advanceName);

	DFSPrint(foundAdvance, 0, DirectionT::UP);
}

void PrintChildren(string advanceName) {
	ptr foundAdvance = FindAdvance(advanceName);

	DFSPrint(foundAdvance, 0, DirectionT::DOWN);
}

void PrintAll() {
	for (auto tree : advances) {
		PrintChildren(tree);
	}
}

void DFSPrint(ptr tree, int depth, DirectionT direction) {
	// print depth tabs
	for (int i = 0; i < depth; i++)
		cout << "\t";

	cout << tree->Advance().Name() << endl;

	switch (direction) {
	case DirectionT::UP:
		for (auto parent : tree->Parents())
			DFSPrint(parent, depth+1, DirectionT::UP);
	}
	case DirectionT::DOWN:
		for (auto parent : tree->Children())
			DFSPrint(parent, depth+1, DirectionT::DOWN);
	}
}
