// Node.C
// Gabriel Dougherty
#include <iostream>
#include "Node.h"
#include "Advance.h"

using namespace std;


const AdvanceT NodeT::Advance() const {
	return advance;
}

void NodeT::AddParent(ptr other) {
	if (other != nullptr) {
		if (!IsChild(other->Advance())) {
			parents.push_back(other);
			other->AddChild(this);
		}
	}
}

void NodeT::AddChild(ptr other) {
	if (other != nullptr) {
		if (!IsParent(other->Advance())) {
			children.push_back(other);
			other->AddParent(this);
		}
	}
}

const vector<ptr> NodeT::Parents() const {
	return parents;
}

const vector<ptr> NodeT::Children() const {
	return children;
}

// helper function
bool NodeT::FindAdvance(const vector<ptr>& nodeList,
						const AdvanceT& other) const {
	// return whether the node was found in the given list
	return find_if(nodeList.cbegin(), nodeList.cend(),
				   [other](const ptr& node) {
					   return node->Advance() == other;})
		!= nodeList.cend();

	// alternate implementation
	/*
	for (auto& node : nodeList)
		if (other == node->Advance())
			return true;
	return false;
	*/
}

bool NodeT::IsParent(const AdvanceT& other) const {
	// return whether the advance was found as a child
	// of this node
	return FindAdvance(children, other);
}

bool NodeT::IsChild(const AdvanceT& other) const {
	// return whether the advance was found as a parent
	// of this node
	return FindAdvance(parents, other);
}
