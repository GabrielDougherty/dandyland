#pragma once
#include "Node.h"
//#include "Forest.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <cstdlib> // atexit
#include <algorithm>

namespace NodeTestUtils {
	const char LINE[] = "------------------------------------------";

	void ReadTreeFile(std::vector<ptr>& nodes, std::ifstream& inFile);
	void BuildTree(std::vector<ptr>& nodes);
	void PrintNodes(const std::vector<ptr> nodes);
	void TestTree(const std::vector<ptr> nodes);
	void DeleteNodes();
}
