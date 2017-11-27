#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool compare(int i, int j) {return i > j; }
int main(){
    int n;
    cin >> n;
    vector<int> countArr;
    int count = 0;
    int b = 1;
    for(int i = 0; i < 32; ++i) {
        if(n & (b << i))
            ++count;
        else {
            countArr.push_back(count);
            count = 0;
        }
    }
    sort(countArr.begin(), countArr.end(), compare);
    cout << countArr[0] << endl;
    return 0;
}
