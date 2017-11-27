/* you only have to complete the function given below.  
Node is defined as  

struct node
{
    int data;
    node* left;
    node* right;
};

*/
struct node {
	int data;
	node *left;
	node *right;
};

int main() {
	
}

void preOrderTraverse(node *root) {
	if(root == NULL)
		return;
		
	node *iter = root;
	while(iter != NULL) {
		if(iter->left == NULL) {
			//it is similiar to the base case in recursion
			cout << iter->data << " ";
			iter = iter->right;
		} else {
			node *temp = iter->left;
			//we aims to find the predecessor of the current iterator
			while(temp->right != NULL && temp->right != iter)
				temp = temp->right;
				
			//once we found that predecessor, we judge whether it is connected to
			//the current iterator. If it is connected, we cut off that connection.
			//Because it means that it is the second time for us to meet the current
			//iterator and the elements of iterator's left-hand side have all been
			//printed. If it is not connected, we build that connection. Because it means
			//that it is our first time to meet the current iterator and the elements of
			//its left-hand side are not printed yet. 
			if(temp->right == NULL) {
				temp->right = iter;
				cout << iter->data << " ";
				iter = iter->left;
			} else {
				temp->right = NULL;
				iter = iter->right;
			}
		}
	}
}

//Morris inOrderTraverse is quite similiar to the preorder.
void inOrderTraverse(node *root) {
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
}

//Morris postOrderTraverse is quite difficult
//you can visit this website for more information
// http://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html
void postOrderTraverse(node *root) {
	if(root == NULL)
		return;
	
	node *dummyRoot = new node;
    dummyRoot->data = 0;
    dummyRoot->left = root;
    dummyRoot->right = NULL;
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
					vec.push_back(temp->data);
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












