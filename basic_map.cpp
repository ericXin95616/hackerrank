#include <map>
#include <iostream>
#include <string>
#include <iterator>

using namespace std;

int main () {
	map<string, int> m;
	int query = 0, type = 0, mark = 0;
	string studName;
	
	cin >> query;
	for( int i = 0; i < query; ++i) {
		cin >> type;
		switch (type) {
			case 1:
			{
				cin >> studName >> mark;
				map<string, int>::iterator it = m.find(studName);
				if ( it == m.end() )
					m.insert(make_pair(studName, mark));
				else 
					it->second += mark;
				break;
			}
			case 2:
			{
				cin >> studName;
				map<string, int>::iterator it = m.find(studName);
				if ( it != m.end() )
					it->second = 0;
				break;
			}
			case 3:
			{
				cin >> studName;
				map<string, int>::iterator it = m.find(studName) ;
				if ( it == m.end() )
					cout << "0" << endl;
				else 
					cout << it->second << endl;
				break;
			}
		}
	}
}
