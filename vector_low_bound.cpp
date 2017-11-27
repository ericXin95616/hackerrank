#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void output(const int arr[], const vector<int> &vec, const int arrSize);
bool compare(int i, int j) {return (i < j);}

int main() {
    int size = 0;
    cin >> size;
    
    vector<int> v;
    for(int i = 0; i < size; ++i) {
    	int temp = 0;
    	cin >> temp;
    	v.push_back(temp);
    }
    
    int query = 0;
    cin >> query;
    int arr[query];
    for(int i = 0; i < query; ++i) {
    	cin >> arr[i];
    }
    output(arr, v, query);
    return 0;
}

void output(const int arr[], const vector<int> &vec, const int arrSize) {
	for(int i = 0; i < arrSize; ++i) {
		auto it = lower_bound(vec.begin(), vec.end(), arr[i], compare);
		if(*it == arr[i]) {
			cout << "Yes" << " ";
		} else {
			cout << "No" << " ";
		}
		cout << it - vec.begin() + 1 << endl;
	}
}






