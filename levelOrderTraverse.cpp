/*
struct node
{
    int data;
    node* left;
    node* right;
}*/

/*
//Function to print level order traversal of tree
printLevelorder(tree)
for d = 1 to height(tree)
   printGivenLevel(tree, d);

//Function to print all nodes at a given level
printGivenLevel(tree, level)
if tree is NULL then return;
if level is 1, then
    print(tree->data);
else if level greater than 1, then
    printGivenLevel(tree->left, level-1);
    printGivenLevel(tree->right, level-1);
*/
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
}

void levelOrder(node * root) {
	for(int i = 0; i < getTreeHeight(root); ++i) {
		printGivenLevel(root, i);
	}
}

void printGivenLevel(node *root, const int level) {
	if(!root)
		return;
	if(level == 0)
		cout << root->data << " ";
	else {
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}





