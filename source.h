#ifndef SOURCE_H
#define SOURCE_H
#include <vector>
using namespace std;
typedef struct node {
	int data;
	node *left;
	node *right;
} node;

node* findNode(node *root, const int parentData);
void addNode(node *root, const int leftData, const int rightData, const int parentData);

int getTreeHeight(node *root);
void nodesLevel(node *root, vector<node*> &nodes, const int level);
//void swapSingleNode(node *swapedNode);
void swapNode(node *root, const int baseLevelNum);

void inorderPrint(node *root);
void freeBT(node **root);

#endif
