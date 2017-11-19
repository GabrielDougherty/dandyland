#ifndef NODE
#define NODE
#include "Advance.h"
#include <iostream>
#include <algorithm>
#include <vector>

class NodeT;

typedef NodeT * ptr;
class NodeT {
public:
	NodeT()=delete;
	NodeT(const NodeT&)=delete;
	NodeT& operator=(const NodeT&)=delete;
	inline NodeT(AdvanceT other) : advance(other) { }
	
	void AddParent(ptr);
	void AddChild(ptr);
	const std::vector<ptr> Parents() const;
	const std::vector<ptr> Children() const;
	const AdvanceT Advance() const;
	bool IsChild(const AdvanceT&) const;
	bool IsParent(const AdvanceT&) const;
private:
	bool FindAdvance(const std::vector<ptr>&,
					 const AdvanceT&) const;

	AdvanceT advance;
	std::vector<ptr> children;
	std::vector<ptr> parents;
};



#endif
