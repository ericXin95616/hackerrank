#include "source.h"
#include <string>
#include <vector>
#include <iostream>
/*
typedef struct node {
	int data;
	node *left;
	node *right;
} node;
*/
using namespace std;

node* findNode(node *root, const int parentData) {
	if(!root)
		return NULL;
	node *currNode = root;
	node *temp = NULL;
	while(currNode) {
		if(currNode->data == parentData) {
			temp = currNode;
		}

		if(!currNode->left) {
			currNode = currNode->right;
		} else {
			node *temp = currNode->left;
			while(temp->right != currNode && temp->right) {
				temp = temp->right;
			}
			if( temp->right == NULL ) {
				temp->right = currNode;
				currNode = currNode->left;
			} else {
				temp->right = NULL;
				currNode = currNode->right;
			}
		}
	}
	
	if( !temp ) {
		cout << "Can't find that parent node!" << endl;
		return temp;
	}
	return temp;
}

void addNode(node *root, const int leftData, const int rightData, const int parentData) {
	if(!root)
		return;
	
	node *parentNode = findNode(root, parentData);
	if(leftData != -1) {
		node *leftNode = new node;
		leftNode->data = leftData;
		leftNode->left = NULL;
		leftNode->right = NULL;
		parentNode->left = leftNode;
	}
	
	if(rightData != -1) {
		node *rightNode = new node;
		rightNode->data = rightData;
		rightNode->left = NULL;
		rightNode->right = NULL;
        parentNode->right = rightNode;
	}
}

int getTreeHeight(node *root) {
	if(root == NULL || (root->left == NULL && root->right == NULL))
		return 1;
	int heightOfLeft = 0, heightOfRight = 0;
	
	if(root->left) {
		heightOfLeft = 1 + getTreeHeight(root->left);
	}
	
	if(root->right) {
		heightOfRight = 1 + getTreeHeight(root->right);
	}
	
	return (heightOfLeft < heightOfRight) ? heightOfRight : heightOfLeft;
}

void nodesLevel(node *root, vector<node*> &nodes, const int level){
	if(!root || level <= 0)
		return;
	
	if(level == 1) {
		nodes.push_back(root);
	} else {
		nodesLevel(root->left, nodes, level - 1);
		nodesLevel(root->right, nodes, level - 1);
	}
}

//do we need to pass node** to complete this function??
/*
void swapSingleNode(node *swapedNode) {
	node *temp = swapNode->left;
	swapNode->left = swapNode->right;
	swapNode->right = temp;
}
*/

void swapNode(node *root, const int baseLevelNum) {
	const int treeHeight = getTreeHeight(root);
	int levelNum = baseLevelNum;
	while(levelNum < treeHeight) {
		vector<node*> nodesInLevel;
		nodesLevel(root, nodesInLevel, levelNum);
		for(int i = 0, size = nodesInLevel.size(); i < size; ++i) {
			node *temp = nodesInLevel[i]->left;
			nodesInLevel[i]->left = nodesInLevel[i]->right;
			nodesInLevel[i]->right = temp;
		}
		levelNum += baseLevelNum;
	}
}

void inorderPrint(node *root) {
	if(root == NULL)
		return;
	
	node *iter = root;
	while(iter != NULL) {
		if(iter->left == NULL) {
			cout << iter->data << " ";
			iter = iter->right;
		} else {
			node *temp = iter->left;
			while(temp->right != NULL && temp->right != iter)
				temp = temp->right;
			if(temp->right == NULL) {
				temp->right = iter;
				iter = iter->left;
			} else {
				temp->right = NULL;
				cout << iter->data << " ";
				iter = iter->right;
			}
		}
	}
	cout << endl;
}

void freeBT(node **root) {
	if( !(*root) )
		return;
		
	if(!(*root)->left && !(*root)->right) {
		free(*root);
		*root = NULL;
		return;
	}
	
	if((*root)->left) {
		freeBT( &( (*root)->left ) );
	}
	
	if((*root)->right) {
		freeBT( &( (*root)->right ) );
	}
	
	freeBT(root);
}








