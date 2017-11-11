#ifndef FOREST
#define FOREST
#include <vector>
#include <string>
#include "Advance.h"
#include "Node.h"

class ForestT {
public:
	inline ForestT() : ForestT("Advance") {}
	ForestT(std::string);

	void AddAdvance(const AdvanceT&);
	ptr FindAdvance(std::string advanceName);
private:
	std::vector<NodeT> roots;
};




#endif
