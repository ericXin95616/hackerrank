/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
   struct Node {
      int data;
      Node* left;
      Node* right;
   }
*/

/*
 * How to check if a tree is a binary search tree?
 * Note that if we print a tree using inorder traverse
 * The result of binary search tree will be an ascending
 * sequence.
*/
#include <vector>

bool checkBST(Node* root) {
	if(!root)
		return true;

	vector<int> inorderTraverse;
	Node *curr = root;
	while(curr) {
		if(!curr->left) {
			inorderTraverse.push_back(curr->data);
			curr = curr->right;
		} else {
			Node *temp = curr->left;
			while(temp->right && temp->right != curr) {
				temp = temp->right;
			}
			if(!temp->right) {
				temp->right = curr;
				curr = curr->left;
			} else {
				temp->right = NULL;
				inorderTraverse.push_back(curr->data);
				curr = curr->right;
			}
		}
	}
	
	for(int i = 0, size = inorderTraverse.size(); i < size - 1; ++i) {
		if(inorderTraverse[i] >= inorderTraverse[i + 1])
			return false;
	}
	return true;
}







