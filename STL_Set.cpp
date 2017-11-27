#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

void add_val(set<int> &intSet, const int val) {intSet.insert(val);}
void delete_val(set<int> &intSet, const int val) {intSet.erase(val);}
bool find_val(const set<int> &intSet, const int val){ return (intSet.end() != intSet.find(val));}

int main() {
    int query = 0;
    cin >> query;
    set<int> s;
    for(int i = 0; i < query; ++i) {
    	int func = 0, val = 0;
    	cin >> func >> val;
    	switch(func) {
    		case 1 : add_val(s, val); break;
    		case 2 : delete_val(s, val); break;
    		case 3 : find_val(s, val) ? cout << "Yes" << endl : cout << "No" << endl; break;
    		default : cout << "We don't have this function!" << endl; break;
    	}
    } 
    return 0;
}




