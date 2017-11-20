#include "NodeTester.h"

using namespace std;

int main() {
	cout << "TESTING NODE" << endl << endl;

	// test with "Advance" input file
	NodeTester tester;

	tester.PrintNodes();
	tester.RunAllTests();
	
	return 0;
}
