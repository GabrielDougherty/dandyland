#ifndef FOREST
#define FOREST
#include <vector>
#include <string>
#include <algorithm>
#include "Advance.h"
#include "Node.h"

enum class DirectionT {UP,DOWN};

class ForestT {
public:
	inline ForestT() : ForestT("Advance") {}
	ForestT(std::string);
	~ForestT();

	bool AdvanceExists(std::string) const;

	void PrintParents(std::string) const;
	void PrintChildren(std::string) const;
	void PrintAll() const;
private:
	void DFSPrint(ptr, int, DirectionT) const;

	ptr DFS(ptr, std::string) const;
	ptr FindAdvance(std::string) const;
	void FixParents(ptr);

	void AddAdvance(/*const*/ AdvanceT);
	void FixAdvances();

	void KillTree(ptr, std::vector<ptr>);
	std::vector<ptr> advances;



	int ADVANCE_ALREADY_EXISTS = 1;
};


#endif
