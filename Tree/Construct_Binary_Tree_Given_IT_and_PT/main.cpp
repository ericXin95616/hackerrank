#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cout;
using std::cin;
using std::queue;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder);
void levelOrderWithQueue(TreeNode *root);

int main() {
  cout << "Please enter your inorder traverse array: ";
  int temp;
  vector<int> inorder;
  while(cin>>temp) {
    inorder.push_back(temp);
  }

  cout << "Please enter your postorder traverse array: ";
  vector<int> postorder;
  cin.clear();
  cin.get();
  while(cin>>temp) {
    postorder.push_back(temp);
  }

  TreeNode* treeRoot = buildTree(inorder, postorder);

  levelOrderWithQueue(treeRoot);
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
  if(inorder.empty() && postorder.empty()) {
    return nullptr;
  }

  int rootVal = postorder.back();
  TreeNode* root = new TreeNode(rootVal);
  //root iterator should not be null, so we didn't consider this situation
  auto inorderBegin = inorder.begin();
  auto inorderEnd = inorder.end();
  auto postorderBegin = postorder.begin();
  auto postorderEnd = postorder.end();

  auto rootIt = std::find(inorderBegin, inorderEnd, rootVal);
  auto leftTreeNodeNumber = rootIt - inorderBegin;
  //auto rightTreeNodeNumber = inorderEnd - rootIt - 1;
  vector<int> inorderLeftTree(inorderBegin, rootIt);
  vector<int> postorderLeftTree(postorderBegin, postorderBegin + leftTreeNodeNumber);
  vector<int> inorderRightTree(rootIt+1, inorderEnd);
  vector<int> postorderRightTree(postorderBegin + leftTreeNodeNumber, postorderEnd - 1);

  root->left = buildTree(inorderLeftTree, postorderLeftTree);
  root->right = buildTree(inorderRightTree, postorderRightTree);
  return root;
}

TreeNode* buildTreePreIn(vector<int> & preorder, vector<int> & inorder) {
  if(inorder.empty() && preorder.empty()) {
    return nullptr;
  }

  int rootVal = preorder.front();
  TreeNode* root = new TreeNode(rootVal);
  //root iterator should not be null, so we didn't consider this situation
  auto inorderBegin = inorder.begin();
  auto inorderEnd = inorder.end();
  auto preorderBegin = preorder.begin();
  auto preorderEnd = preorder.end();

  auto rootIt = std::find(inorderBegin, inorderEnd, rootVal);
  auto leftTreeNodeNumber = rootIt - inorderBegin;
  //auto rightTreeNodeNumber = inorderEnd - rootIt - 1;
  vector<int> inorderLeftTree(inorderBegin, rootIt);
  vector<int> preorderLeftTree(preorderBegin + 1, preorderBegin + leftTreeNodeNumber + 1);
  vector<int> inorderRightTree(rootIt+1, inorderEnd);
  vector<int> preorderRightTree(preorderBegin + leftTreeNodeNumber + 1, preorderEnd);

  root->left = buildTree(preorderLeftTree, inorderLeftTree);
  root->right = buildTree(preorderRightTree, inorderRightTree);
  return root;
}

void levelOrderWithQueue(TreeNode *root) {
  //this queue is used to store the children node
  queue<TreeNode*> q;
  TreeNode *temp = root;
  while(temp != nullptr) {
    cout << temp->val << " ";
    if(temp->left != nullptr)
      q.push(temp->left);
    if(temp->right != nullptr)
      q.push(temp->right);
    if(q.empty())
      break;
    else {
      temp = q.front();
      q.pop();
    }
  }
}