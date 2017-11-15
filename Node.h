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
	const vector<ptr> Parents() const;
	const vector<ptr> Children() const;
	const AdvanceT Advance() const;
	bool IsChild(const AdvanceT&);
	bool IsParent(const AdvanceT&);
private:
	AdvanceT advance;
	std::vector<ptr> children;
	std::vector<ptr> parents;
};



#endif
