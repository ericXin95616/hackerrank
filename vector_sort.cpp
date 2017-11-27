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
    
    sort(v.begin(), v.end(), compare);
    
    for(int i = 0; i < size; ++i) {
    	cout << v[i] << " ";
    }
    return 0;
}
