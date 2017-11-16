#ifndef FOREST
#define FOREST
#include <vector>
#include <string>
#include "Advance.h"
#include "Node.h"

enum class DirectionT {UP,DOWN,LEFT,RIGHT};

class ForestT {
public:
	inline ForestT() : ForestT("Advance") {}
	ForestT(std::string);
	~ForestT();

	bool AdvanceExists(std::string);

	void PrintParents(std::string);
	void PrintChildren(std::string);
	void PrintAll();
private:
	void DFSPrint(ptr, int, DirectionT);

	ptr DFS(ptr, std::string);
	ptr FindAdvance(std::string);
	void FixParents(ptr);

	void AddAdvance(/*const*/ AdvanceT);
	void FixAdvances();

	void KillTree(ptr, std::vector<ptr>);
	std::vector<ptr> advances;



	int ADVANCE_ALREADY_EXISTS = 1;
};


#endif
