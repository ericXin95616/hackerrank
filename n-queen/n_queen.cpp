#include <iostream>
#include <sstream>
#include "broad.h"
#include "queen.h"

using std::cin;
using std::cout;
using std::endl;
using std::stringstream;

int main(const int argc, const char* argv[]) {
	if(argc != 2) {
		cout << "Wrong Command Line Instruction!" << endl;
		cout << "Program ends!" << endl;
		return 0;
	}
	
	//Input verify
	stringstream ss(argv[1]);
	int n = 0;
	ss >> n;
	if(n != 1 && n < 4) {
		cout << "No Solution!" << endl;
		return 0;
	}
	
	char** broad = broadCreation(n, n);
	find_n_queen(broad, n, 0);
	freebroad(&broad, n);
}
