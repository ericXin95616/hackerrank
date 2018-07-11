#include <iostream>
#include <cstdlib>
#include <ctime>
#include "red_black_tree.h"
#include "json.hpp"

using nlohmann::json;
using std::cout;
using std::endl;
using std::cin;

int main() {
  int numInsertion = 0;
  cout << "Please enter how many numbers you want to insert: ";
  cin >> numInsertion;

  red_black_tree<int, double> rbTree;

  srand(time(0));
  for (int i = 0; i < numInsertion; ++i) {
    int randomNum = rand() % 100 + 1; // random number from 1 - 100
    cout << "The random number is " << randomNum << endl;
    rbTree.insert(randomNum);
    cout << "The red black tree: " << endl;
    cout << rbTree.JSON().dump(2) << endl;
  }
  /*
  cout << "\n\n\nBegin to removeMin from red black tree:\n";
  while(!rbTree.isempty()) {
    cout << "After removing min:\n";
    rbTree.removeMin();
    cout<< rbTree.JSON().dump(2) << endl;
  }
   */
  cout << "\n\n\nBegin to removeMax from red black tree:\n";
  while(!rbTree.isempty()) {
    cout << "After removing max:\n";
    rbTree.removeMax();
    cout<< rbTree.JSON().dump(2) << endl;
  }
}