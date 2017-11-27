#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "source.h"
using namespace std;
/*
typedef struct node {
	int data;
	node *left;
	node *right;
} node;

void addNode(node *root, const int leftData, const int rightData, const int parentNode);
void swapNode(node *root, const int baseLevelNum);
string inorderPrint(node *root);
void freeBT(node *root);
*/
int main() {
	node *root = new node;
	root->data = 1;
	root->left = NULL;
	root->right = NULL;
	
	int N = 0, T = 0;
	cin >> N;
	for(int i = 1; i <= N; ++i) {
		int left = 0, right = 0;
		cin >> left >> right;
		addNode(root, left, right, i);
	}
	
	cin >> T;
	for(int i = 0; i < T; ++i) {
		int baseLevel = 0;
		cin >> baseLevel;
		swapNode(root, baseLevel);
		inorderPrint(root);
	}
	
	freeBT(&root);
    return 0;
}






