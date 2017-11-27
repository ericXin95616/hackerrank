int getTreeHeight(node *root) {
	if(root == NULL || (root->left == NULL && root->right == NULL))
		return 0;
	int heightOfLeft = 0, heightOfRight = 0;
	
	if(root->left) {
		heightOfLeft = 1 + getTreeHeight(root->left);
	}
	
	if(root->right) {
		heightOfRight = 1 + getTreeHeight(root->right);
	}
	
	return (heightOfLeft < heightOfRight) ? heightOfRight : heightOfLeft;
	/*
	if(root == NULL || (root->left == NULL && root->right == NULL))
		return 0;
		
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
				cout << iter->data << " ";
				iter = iter->left;
			} else {
				temp->right = NULL;
				iter = iter->right;
			}
		}
	}
	*/
}
