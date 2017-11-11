#include <iostream>
#include "Node.h"
#include "Advance.h"

using namespace std;


const AdvanceT NodeT::Advance() const {
	return advance;
}

bool NodeT::IsChild(const AdvanceT& other) {
	for (auto& parent : parents) // maybe use &&
		if (other == parent->Advance())
			return true;
	return false;
}

bool NodeT::IsParent(const AdvanceT& other) {
	for (auto& child : children)
		if (other == child->Advance())
			return true;
	return false;
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
