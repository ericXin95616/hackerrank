#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> parseInts(string str) {
   stringstream ss(str);
   vector<int> integers;
   char ch;
   int temp;
   while(!ss.eof()) {
   		ss >> temp >> ch;
   		//cout << temp << endl;
   		integers.push_back(temp);
   }
   return integers;
}

int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(unsigned int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    //cout << integers.size() << endl;
    return 0;
}

