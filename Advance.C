#include "Advance.h"
#include <string>
#include <iostream>

using namespace std;

AdvanceT::AdvanceT(){
}

AdvanceT::AdvanceT(string line) {
   size_t pos;
   string tmp;

   // remove the name;
   pos = line.find(',');
   name = line.substr(0,pos);
   line = line.substr(pos+1, line.size());


   // remove the pre-req
   pos = line.find(',');
   tmp = line.substr(0,pos);
   line = line.substr(pos+1,line.size());
   size_t bpos;
   if (tmp != "-") {
      bpos = tmp.find(';');
      while(bpos != string::npos) {
         prereq.push_back(tmp.substr(0,bpos));
	 tmp = tmp.substr(bpos+1,tmp.size());
         bpos = tmp.find(';');
      }
      prereq.push_back(tmp);
   }
   return;
}

// observers
string AdvanceT::Name() const{
    return name;
}

vector<string> AdvanceT::Requirements() const{
    return prereq;
}

// operators
bool AdvanceT::operator==(const AdvanceT& other) const {
	return name == other.name;
}

bool AdvanceT::operator!=(const AdvanceT& other) const {
	return name != other.name;
}
