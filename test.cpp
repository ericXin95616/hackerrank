#include <iostream>
#include <string>

using namespace std;

string getTagName(string tagStr) {
	string delimiter1("<"), delimiter2("\n"), delimiter3(" ");
	string firstLine = tagStr.substr(tagStr.find(delimiter1) + delimiter1.length(), tagStr.find(delimiter2) - delimiter2.length());
	string tagName = "";
	if (firstLine.find(delimiter3) != string::npos) {
		tagName = firstLine.substr(0, firstLine.find(delimiter3));
	} else {
		string delimiter4(">");
		tagName = firstLine.substr(0, firstLine.find(delimiter4));
	}
	return tagName;
}

int main() {
	int numLine;
	//cout << "Enter the number of lines: ";
	cin >> numLine;
	cin.get();//skip '\n'
	
	//We first use a for loop to read all the input into a single string
	//cout << "Enter the input: " << endl;
	string allInput, temp;
	for(int i = 0; i < numLine; ++i) {
		getline(cin, temp);
		temp += "\n";
		allInput += temp;
	}
	
	cout << getTagName(allInput) << endl;
}
