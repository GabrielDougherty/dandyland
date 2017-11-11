#ifndef NODE
#define NODE
#include "Advance.h"
#include <iostream>
#include <memory>
#include <vector>

class NodeT;

typedef NodeT * ptr;

class NodeT {
public:
	NodeT()=delete;
	NodeT(AdvanceT other) : advance(other) { } ;
	void AddParent(ptr);
	void AddChild(ptr);
	const AdvanceT Advance() const;
private:
	AdvanceT advance;
	bool IsChild(const AdvanceT&);
	bool IsParent(const AdvanceT&);
	std::vector<ptr> children;
	std::vector<ptr> parents;
};



#endif
