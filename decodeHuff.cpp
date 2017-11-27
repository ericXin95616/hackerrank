/* 
The structure of the node is

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;
    
}node;

*/


void decode_huff(node * root,string s)
{
	if(!root)
		return;
		
    string decode;
    node *currNode = root;
    //what if Huffman tree only has one root node??
    for(int i = 0, auto size = s.length(); i < size; ++i) {
    	if(s[i] == '1')
    		currNode = currNode->right;
    	if(s[i] == '0')
    		currNode = currNode->left;
    	if(!currNode->left && !currNode->right) {
    		decode += currNode->data;
    		currNode = root;
    	}
    }
    cout << decode << endl;
}




