#ifndef AVL_TREE_CLASS_H
#define AVL_TREE_CLASS_H
#include <iostream>
#include <vector>

using namespace std;
typedef int Type;

typedef struct AVL_Node {
	Type val;
	int ht;
	AVL_Node *left;
	AVL_Node *right;
	AVL_Node(const Type value = 0) {
		val = value;
		ht = 0;
		left = NULL;
		right = NULL;
	}
} node;

class AVL_Tree {
	private:
		node *root = NULL;
		
	public:
		AVL_Tree() = default;
		AVL_Tree(const Type *arr, const unsigned int &size);
		AVL_Tree(const vector<Type> &vec);
		AVL_Tree(const AVL_Tree &tree) { root = NULL; }
		~AVL_Tree();
		
		AVL_Tree& operator=(const AVL_Tree &tree) { return *(this);}
		//默认前序遍历
		friend ostream& operator<<(ostream& os, const AVL_Tree &tree);
		
		void AVL_Insert(const Type &value) {
			root = AVL_Insert(root, value);
		}
		
		void AVL_Delete(const Type &value) {
			root = AVL_Delete(root, value);
		}
		
		//循环实现树的打印
		void preorderPrint() const;
		void inorderPrint() const;
		void postorderPrint() const;
		
		//打印树的详细信息
		void printTree() const;
	
	private:
		node* LL_Rotation(node*);
		node* RR_Rotation(node*);
		node* LR_Rotation(node*);
		node* RL_Rotation(node*);
		int height(const node* curr) { 
			if(curr == NULL)
				return -1;
			return curr->ht; 
		}
		int max(const int &a, const int &b) { return (a > b) ? a : b; }
		
		node* AVL_Insert(node *root, const Type &value);
		node* AVL_Delete(node *root, const Type &value);
		void printTree(const node* root) const;
};
#endif



