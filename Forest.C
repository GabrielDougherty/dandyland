#include "Forest.h"
#include <iostream>
#include <fstream>

using namespace std;

ForestT::ForestT(string filename) {
	ifstream inFile(filename);

	string line;

	while (getline(inFile, line))
		AddAdvance(AdvanceT(line));
	FixAdvances();
}

void ForestT::AddAdvance(AdvanceT newAdvance) {
	if (FindAdvance(newAdvance.Name() != nullptr))
		throw ADVANCE_ALREADY_EXISTS;

	ptr foundAdvance;
	bool isChild = false;

	for (auto req : newAdvance.Requirements()) {
		foundAdvance = FindAdvance(req);
		if (foundAdvance != nullptr) {
			foundAdvance->AddChild(&newAdvance);
			isChild = true;
		}
	}
	if (!isChild)
		advances.push_back(newAdvance);
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

ptr DFS(ptr tree, string advanceName) {
	if (ptr == nullptr)
		return nullptr;
	if (ptr->Advance().Name() == advanceName)
		return ptr;
	else
		for (auto child : ptr->Children())
			DFS(child, nodeName);
	// return nullptr; ???maybe???
}

