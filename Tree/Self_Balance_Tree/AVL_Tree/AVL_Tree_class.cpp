#include "AVL_Tree_class.h"
#include <iostream>
#include <vector>

node* AVL_Tree::LL_Rotation(node* root) {
	node *changedRoot = root->left;
	node *temp = root->left->right;
	root->left->right = root;
	root->left = temp;
	
	root->ht = max(height(root->left), height(root->right)) + 1;
	changedRoot->ht = max(height(changedRoot->left), height(changedRoot->right)) + 1;
	return changedRoot;
}

node* AVL_Tree::RR_Rotation(node* root) {
	node *changedRoot = root->right;
	node *temp = root->right->left;
	root->right->left = root;
	root->right = temp;
	
	root->ht = max(height(root->left), height(root->right)) + 1;
	changedRoot->ht = max(height(changedRoot->left), height(changedRoot->right)) + 1;
	return changedRoot;
}

node* AVL_Tree::LR_Rotation(node* root) {
	root->left = RR_Rotation(root->left);
	root = LL_Rotation(root);
	return root;
}

node* AVL_Tree::RL_Rotation(node* root) {
	root->right = LL_Rotation(root->right);
	root = RR_Rotation(root);
	return root;
}
//利用数组初始化 AVL树
//将数组的第一个元素作为根节点，其余元素依次加到这个树中
AVL_Tree::AVL_Tree(const Type *arr, const unsigned int & size) {
	for(unsigned int i = 0; i < size; ++i) {
		root = AVL_Insert(root, arr[i]);
	}
}

//同上
AVL_Tree::AVL_Tree(const vector<Type> &vec) {
	for(auto it = vec.begin(), endIt = vec.end(); it != endIt; ++it) {
		root = AVL_Insert(root, *it);
	}
}

//拷贝构造函数
/*
AVL_Tree::AVL_Tree(const AVL_Tree &tree) {
	
}
*/

//postOrder traverse and delete
AVL_Tree::~AVL_Tree(){
	if(root == NULL)
		return;
	
	node *dummyRoot = new node();
    //dummyRoot->data = 0;
    dummyRoot->left = root;
    //dummyRoot->right = NULL;
	node *iter = dummyRoot;
	while(iter) {
		if(iter->left == NULL) {
			//cout << iter->data << " ";
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
				vector<node*> vec;
				temp = iter->left;
				while(temp != NULL) {
					vec.push_back(temp);
					temp = temp->right;
				}
				while(!vec.empty()) {
					node *deletedNode = vec.back();
					vec.back() = NULL;
					delete deletedNode;//delete, but not set that node to NULL, which might cause problem
					vec.pop_back();
				}
				iter = iter->right;
			}
		}
	}
	delete dummyRoot;
}

node* AVL_Tree::AVL_Insert(node* root, const Type &value){
	node *insertNode = new node;
	insertNode->val = value;
	insertNode->ht = 0; // 定义空树的高度为-1，叶子的高度为0
	insertNode->left = NULL;
	insertNode->right = NULL;
    
    if(!root) {
      // if root is NULL
      // we let insertNode as root
    	root = insertNode;
        return root;
    }
    
	if(value < root->val) {
		// this step is the same as BST insert
		root->left = AVL_Insert(root->left, value);
		
		//LL_Rotation or LR_Rotation
		//No need to judge whether it is RR_Rotation or RL_Rotation
		if ( height(root->left) - height(root->right) == 2) {
			// LL_Rotation
			if( height(root->left->left) > height(root->left->right) ) {
				root = LL_Rotation(root);
			} else {
			//LR_Rotation
				root = LR_Rotation(root);
			}
		}
	} else if (value > root->val){
		root->right = AVL_Insert(root->right, value);
		
		//RR_Rotation or RL_Rotation
		if( height(root->left) - height(root->right) == -2) {
			//RR_Rotation
			if(height(root->right->right) > height(root->right->left)) {
				root = RR_Rotation(root);
			} else {
			//RL_Rotation
				root = RL_Rotation(root);
			}
		}
	}
	
	root->ht = max(height(root->left), height(root->right)) + 1;
   return root;
}

//haven't test yet!!!
node* AVL_Tree::AVL_Delete(node* root, const Type &value) {
	 if(!root) {
	 	cout << "No such value exist in this AVL Tree!" << endl;
	 	return root;
	 }
	 
	 if(value < root->val) {
	 	root->left = AVL_Delete(root->left, value);
	 	//need to judge whether it is balanced or not
	 	//LL_Rotation or LR_Rotation
		//No need to judge whether it is RR_Rotation or RL_Rotation
		if ( height(root->left) - height(root->right) == 2) {
			// LL_Rotation
			if( height(root->left->left) > height(root->left->right) ) {
				root = LL_Rotation(root);
			} else {
			//LR_Rotation
				root = LR_Rotation(root);
			}
		}
	 } else if(value > root->val) {
	 	root->right = AVL_Delete(root->right, value);
	 	//same as above
	 	//RR_Rotation or RL_Rotation
		if( height(root->left) - height(root->right) == -2) {
			//RR_Rotation
			if(height(root->right->right) > height(root->right->left)) {
				root = RR_Rotation(root);
			} else {
			//RL_Rotation
				root = RL_Rotation(root);
			}
		}
	 } else if(value == root->val) {
	 	//judge if the node we need to delete is a leaf
	 	if( !height(root) ) {
	 		delete root;//or delete root?
	 		return NULL;
	 	} else {
	 		//删除中间节点
	 		//如果删除节点的左子树不为空，我们用他的前置节点替换要删除的节点
	 		if(root->left) {
	 			//现在temp就是root的前置节点
	 			node *temp = root->left;
	 			while(temp->right != NULL)
	 				temp = temp->right;
	 			Type data = root->val;
	 			root->val = temp->val;
	 			temp->val = data;
	 			root->left = AVL_Delete(root->left, value);
	 		} else {
	 			//如果左子树为空，我们用他的后置节点替换他
	 			node *temp = root->right;
	 			while(temp->left != NULL)
	 				temp = temp->left;
	 			Type data = root->val;
	 			root->val = temp->val;
	 			temp->val = data;
	 			root->right = AVL_Delete(root->right, value);
	 		}
	 	}
	 }
	 root->ht = max(height(root->left), height(root->right)) + 1;
	 return root;
}

void AVL_Tree::preorderPrint() const {
	if(root == NULL) {
		cout << "It is a NULL AVL tree!";
		return;
	}
		
	node *iter = root;
	while(iter != NULL) {
		if(iter->left == NULL) {
			//it is similiar to the base case in recursion
			cout << iter->val << " ";
			iter = iter->right;
		} else {
			node *temp = iter->left;
			//we aims to find the predecessor of the current iterator
			while(temp->right != NULL && temp->right != iter)
				temp = temp->right;
			if(temp->right == NULL) {
				temp->right = iter;
				cout << iter->val << " ";
				iter = iter->left;
			} else {
				temp->right = NULL;
				iter = iter->right;
			}
		}
	}
}

void AVL_Tree::inorderPrint() const {
	if(root == NULL) {
		cout << "It is a NULL AVL tree!";
		return;
	}
	
	node *iter = root;
	while(iter != NULL) {
		if(iter->left == NULL) {
			cout << iter->val << " ";
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
				cout << iter->val << " ";
				iter = iter->right;
			}
		}
	}
}

void AVL_Tree::postorderPrint() const {
	if(root == NULL) {
		cout << "It is a NULL AVL tree!";
		return;
	}
		
	node *dummyRoot = new node(0);
    dummyRoot->left = root;
	node *iter = dummyRoot;
	while(iter) {
		if(iter->left == NULL) {
			//cout << iter->data << " ";
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
				vector<int> vec;
				temp = iter->left;
				while(temp != NULL) {
					vec.push_back(temp->val);
					temp = temp->right;
				}
				while(!vec.empty()) {
					cout << vec.back() << " ";
					vec.pop_back();
				}
				iter = iter->right;
			}
		}
	}
	delete dummyRoot;
}

ostream& operator<<(ostream& os, const AVL_Tree &tree) {
	if(tree.root == NULL) {
		os << "It is a NULL AVL tree!";
		return os;
	}
		
	node *iter = tree.root;
	while(iter != NULL) {
		if(iter->left == NULL) {
			//it is similiar to the base case in recursion
			os << iter->val << " ";
			iter = iter->right;
		} else {
			node *temp = iter->left;
			//we aims to find the predecessor of the current iterator
			while(temp->right != NULL && temp->right != iter)
				temp = temp->right;
			if(temp->right == NULL) {
				temp->right = iter;
				os << iter->val << " ";
				iter = iter->left;
			} else {
				temp->right = NULL;
				iter = iter->right;
			}
		}
	}
	
	return os;
}

void AVL_Tree::printTree() const {
	printTree(root);
}

void AVL_Tree::printTree(const node *root) const{
	if(!root) {
		cout << "It is a null AVL Tree!" << endl;
		return;
	}
	
	if(root->left) {
		cout << root->val << "'s left child is " << root->left->val << endl;
		printTree(root->left);
	} else {
		cout << root->val << "'s left child is null" << endl;
	}
	
	if(root->right) {
		cout << root->val << "'s right child is " << root->right->val << endl;
		printTree(root->right);
	} else {
		cout << root->val << "'s right child is null" << endl;
	}
} 












