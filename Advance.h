#ifndef ADVANCE
#define ADVANCE

#include <string>
#include <vector>

class AdvanceT{
 public:
	AdvanceT(void);
	AdvanceT(std::string);

	// observers
	std::string Name(void) const;
	std::vector<std::string> Requirements(void) const;

	// operators
	bool operator==(const AdvanceT&) const;
	bool operator!=(const AdvanceT&) const;

 private:
   	std::string name;
	std::vector<std::string> prereq;
};

#endif
