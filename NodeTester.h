#pragma once
#include "Node.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <cstdlib> // atexit
#include <algorithm>


class NodeTester {
public:
	inline NodeTester() : NodeTester("Advance") {}
	NodeTester(std::string);
	~NodeTester();
	
	void PrintNodes() const;
	void RunAllTests() const;
	std::vector<ptr> Nodes() const;
private:
	void TestIsChild(const int) const;
	void TestIsParent(const int) const;

	void TestParents(const int) const;
	void TestChildren(const int) const;

	void ReadFile(std::string filename);
	void BuildTree();

	const char * LINE = "------------------------------------------";
	std::vector<ptr> nodes;
};
