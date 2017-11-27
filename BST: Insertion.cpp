/*
Node is defined as 

typedef struct node
{
   int data;
   node * left;
   node * right;
}node;

*/


node * insert(node * root, int value) {
	node *insertNode = new node;
	insertNode->data = value;
	insertNode->left = NULL;
	insertNode->right = NULL;
    
    if(!root) {
        return insertNode;
    }
    
	node *currNode = root;

	while(currNode) {
		if(currNode->data == value)
			break;
			
		if(currNode->data < value) {
			if ( !currNode->right ) {
				currNode->right = insertNode;
				break;
			}
			currNode = currNode->right;
		} else {
			if( !currNode->left ) {
				currNode->left = insertNode;
				break;
			}
			currNode = currNode->left;
		}
	}
   return root;
}


