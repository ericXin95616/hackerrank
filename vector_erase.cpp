#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool compare(int i, int j) { return i < j;}

int main() {
    int size = 0;
    cin >> size;
    
    vector<int> v;
    for(int i = 0; i < size; ++i) {
    	int temp = 0;
    	cin >> temp;
    	v.push_back(temp);
    }
    
    int pos = 0;
    cin >> pos;
    v.erase(v.begin() + pos - 1);
    
    int pos1 = 0, pos2 = 0;
    cin >> pos1 >> pos2;
    v.erase(v.begin() + pos1 - 1, v.begin() + pos2 - 1);
    
    cout << v.size() << endl;
    for(unsigned int i = 0; i < v.size(); ++i) {
    	cout << v[i] << " ";
    }
    return 0;
}
