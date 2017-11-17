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
	NodeT(const NodeT&)=delete;
	NodeT& operator=(const NodeT&)=delete;
	NodeT(AdvanceT other) : advance(other) { } ;
	void AddParent(ptr);
	void AddChild(ptr);
	const std::vector<ptr> Parents() const;
	const std::vector<ptr> Children() const;
	const AdvanceT Advance() const;
	bool IsChild(const AdvanceT&);
	bool IsParent(const AdvanceT&);
	// bool operator==(const NodeT&) const;
private:
	AdvanceT advance;
	std::vector<ptr> children;
	std::vector<ptr> parents;
};



#endif
