#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Thing {
public:
	string GetName() const {return name;};
	void SetName(string n) {name = n;};
	bool operator==(const Thing& other) const {
		return name == other.name;
	};
	bool operator!=(const Thing& other) const {
		return name !=other.name;
	};

private:
	string name;
};

class NodeT;

typedef NodeT * ptr;

class NodeT {
public:
	NodeT()=delete;
	NodeT(Thing other) : thing(other) { } ;
	void AddParent(ptr);
	void AddChild(ptr);
	const Thing GetThing() const;
private:
	Thing thing;
	bool IsChild(const Thing&);
	bool IsParent(const Thing&);
	vector<ptr> children;
	vector<ptr> parents;
};

const Thing NodeT::GetThing() const {
	return thing;
}

bool NodeT::IsChild(const Thing& other) {
	for (auto& parent : parents) // maybe use &&
		if (other == parent->GetThing())
			return true;
	return false;
}

bool NodeT::IsParent(const Thing& other) {
	for (auto& child : children)
		if (other == child->GetThing())
			return true;
	return false;
}

void NodeT::AddParent(ptr other) {
	if (other != nullptr) {
		if (!IsChild(other->GetThing())) {
			parents.push_back(other);
			other->AddChild(this);
		}
	}
}

void NodeT::AddChild(ptr other) {
	if (other != nullptr) {
		if (!IsParent(other->GetThing())) {
			children.push_back(other);
			other->AddParent(this);
		}
	}
}


int main() {
	Thing someThing;
	someThing.SetName("Bill");
	NodeT testNode(someThing);
	return 0;
}
