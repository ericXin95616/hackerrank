#include <iostream>
#include <string>
#include <utility>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::swap;

int main() {
	string str1, str2;
	cin >> str1 >> str2;
	
	auto length1 = str1.size();
	auto length2 = str2.size();
	
	cout << length1 << " " << length2 << endl;
	cout << str1 + str2 << endl;
	
	/*
	char temp = str1[0];
	str1[0] = str2[0];
	str2[0] = temp;
	*/
	//need to judge whether string is empty or not before using the function "substr"
	//cout << str2.front() << str1.substr(1, str1.size() - 1) << " " << str1.front() << str2.substr(1, str2.size() - 1) << endl;
	
	swap(str1[0], str2[0]);
	cout << str1 << ' ' << str2 << endl;
}
