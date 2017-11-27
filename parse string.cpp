#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;

string getTagName(string tagStr);
int parseString(string tagStr, std::vector<string> *seperatedTag);
int parseLine(string aimLine, std::vector<string> *arrayVarName);
string handleQuery(string &query);
void handleTagStr(string tagStr, std::vector<string> *seperatedTag);
string findAimTag(string query, std::vector<string> seperatedTag);

//return tagname in the first line of tagStr
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

//try to use recursion to divide string into different parts
//return vector.size()
int parseString(string tagStr, std::vector<string> *seperatedTag) {
	string tagName = getTagName(tagStr);
	string tagEnd = "</" + tagName + ">\n";
	string temp = tagStr.substr(0, tagStr.find(tagEnd) + tagEnd.length());
	seperatedTag->push_back(temp);
	tagStr.erase(0, tagStr.find(tagEnd) + tagEnd.length());
	if (tagStr.length() > 0)
		return parseString(tagStr, seperatedTag);
	else
		return seperatedTag->size();
}

//add different varName to the vector
int parseLine(string aimLine, std::vector<string> *arrayVarName) {
	string temp = aimLine.substr(0, aimLine.find(" "));
	arrayVarName->push_back(temp);
	aimLine.erase(0, aimLine.find("\"") + strlen("\""));
	aimLine.erase(0, aimLine.find("\"") + strlen("\""));
	if(aimLine[0] != '>') {
		aimLine.erase(0, aimLine.find(" ") + strlen(" "));
		return parseLine(aimLine, arrayVarName);
	}
	return arrayVarName->size();
}

//return the first tag name in query and erase it
//if its first charactor is '~',delete it and return the rest of query
string handleQuery(string &buf) {
	string delimiter("."), parseString;
	size_t pos = 0;
	
	if ((pos = buf.find(delimiter)) != string::npos) {
		parseString = buf.substr(0, pos);
		buf.erase(0, pos + delimiter.length());
	} else {
		if (buf[0] != '~') {
			parseString = buf.substr(0, buf.find("~"));
			buf.erase(0, buf.find("~"));
		} else {
			parseString = buf.erase(0, buf.find("~") + strlen("~"));
		}
	}
	
	return parseString;
}

//We delete the first line and the last line and refer to parseString
void handleTagStr(string tagStr, std::vector<string> *seperatedTag) {
	while(!seperatedTag->empty()) {
		seperatedTag->pop_back();
	}
	
	string delimiter("\n");
	string tagName = getTagName(tagStr);
	string tagEnd = "</" + tagName + ">\n";
	tagStr.erase(0, tagStr.find(delimiter) + delimiter.length());
	tagStr.erase(tagStr.find(tagEnd), tagStr.find(tagEnd) + tagEnd.length());
	
	parseString(tagStr, seperatedTag);
	return;
}


string findAimTag(string query, std::vector<string> seperatedTag) {
	string temp = handleQuery(query);
	
	int vectorSize = seperatedTag.size();
	int count = 0;    //indicate which tapstr contains the name the query seek
	for (int i = 0; i < vectorSize; ++i) {
		if (temp != getTagName(seperatedTag[i]))
			count++;
		else break;
	}
	
	if (count < vectorSize) {
		 if (query[0] == '~') {
		 	string varName = handleQuery(query);
		 	//cout << "\nVariable Name: " << varName << endl;
		 	string firstLine = seperatedTag[count].substr(0, seperatedTag[count].find("\n"));
		 	
		 	if(firstLine.find(" ") != string::npos) {
		 		firstLine.erase(0, firstLine.find(" ") + strlen(" "));
		 		//cout << "Original firstLine: " << firstLine << endl;
		 	} else return "Not Found!\n";
		 	
		 	std::vector<string> arrayVarName;
		 	int vectorSize = parseLine(firstLine, &arrayVarName);
		 	for(int i = 0; i < vectorSize; ++i) {
		 		if(arrayVarName[i] == varName) {
		 			firstLine.erase(0, firstLine.find(arrayVarName[i]) + arrayVarName[i].size() + strlen(" = \""));
		 			//cout << "Variable Name: " << arrayVarName[i] << endl;
		 			//cout << "Original First Line: " << firstLine << endl;
		 			firstLine.erase(firstLine.find("\""), firstLine.find(">") + strlen(">"));
		 			//cout << "First line: " << firstLine << endl;
		 			return firstLine + "\n";
		 		}
		 	}
		 	return "Not Found!\n";
		 } else {
		 	handleTagStr(seperatedTag[count], &seperatedTag);
		 	return findAimTag(query, seperatedTag);
		 }
	}
	
	return "Not Found!\n";
}

int main() {
	int numLine, numQuery;
	//cout << "Enter the number of lines: ";
	cin >> numLine >> numQuery;
	cin.get();//skip '\n'
	
	//We first use a for loop to read all the input into a single string
	//cout << "Enter the input: " << endl;
	string allInput, temp;
	for(int i = 0; i < numLine; ++i) {
		getline(cin, temp);
		temp += "\n";
		allInput += temp;
	}
	
	//try to use recursion to divide string into different parts
	//and store them in the vector
	std::vector<string> seperatedTag;
	parseString(allInput, &seperatedTag);
	
	//cout << "Enter the query: " << endl;
	string query;
	for (int i = 0; i < numQuery; ++i) {
		getline(cin, query);
		cout << findAimTag(query, seperatedTag);
	}
}

