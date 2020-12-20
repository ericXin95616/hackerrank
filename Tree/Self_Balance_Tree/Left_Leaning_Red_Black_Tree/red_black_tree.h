//
// Created by xinbochao on 18-5-1.
//

#ifndef RED_BLACK_TREE_RED_BLACK_TREE_H
#define RED_BLACK_TREE_RED_BLACK_TREE_H

#include <vector>
#include <utility>
#include <queue>
#include "json.hpp"

using std::vector;
using nlohmann::json;
using std::queue;

template <typename Key, typename Value>
class Node{
 public:
  Key key;
  Value val;
  Node<Key, Value> *left;
  Node<Key, Value> *right;
  bool color; // color of link from parent to this child
  int height; // height of the tree, the height of single
              // Node is 0

  Node(const Key &key, const Value &val, bool color):
      key(key), val(val), color(color) {
    left = NULL;
    right = NULL;
    height = 0;
  }
};

/*
 * more accurately speaking, it is the left-leaning
 * red-black tree
 */
template <typename Key, typename Value>
class red_black_tree {
 public:
  red_black_tree();
  explicit red_black_tree(const vector<std::pair<Key, Value>> &vec); // insert element from a vector
  explicit red_black_tree(const vector<Key> &vec);
	
  void insert(const Key &key);
  void insert(const std::pair<Key, Value> &element);
  void remove(const Key &key);
  void removeMin();
  void removeMax();

  bool isempty() const {return root == NULL;}
  json JSON() const; // transform the red black tree to json
  ~red_black_tree();

 private:
  //TODO: want to add a "less" function that allows users
  //TODO: to provide their own definition
  Node<Key, Value>* rotateLeft(Node<Key, Value> *root);
  Node<Key, Value>* rotateRight(Node<Key, Value> *root);
  void flipColors(Node<Key, Value> *root);
  int height(Node<Key,Value> *root) const;
  bool isRed(Node<Key, Value> *node) const;
  Node<Key, Value>* insert(Node<Key, Value>* node, Node<Key, Value>* insertNode);

  Node<Key, Value>* remove(Node<Key, Value>* node, const Key &key);
  Node<Key, Value>* removeMin(Node<Key, Value>* node);
  Node<Key, Value>* removeMax(Node<Key, Value>* node);
  bool isTwoNode(Node<Key, Value>* node) const;
  Node<Key, Value>* redLeftChild(Node<Key, Value>* node);
  Node<Key, Value>* redRightChild(Node<Key, Value>* node);
  Node<Key, Value>* combineParentAndChild(Node<Key, Value>* node);
  Node<Key, Value>* rebalanceTree(Node<Key, Value>* node);

  void deleteTree(Node<Key, Value> *root);
  json printNode(Node<Key, Value> *node) const;
  void swapNode(Node<Key, Value>* node1, Node<Key, Value>* node2);

  Node<Key, Value> *root;
  static bool RED;
  static bool BLACK;
};

template <typename Key, typename Value>
bool red_black_tree<Key, Value>::RED = true;

template <typename Key, typename Value>
bool red_black_tree<Key, Value>::BLACK = false;

template <typename Key, typename Value>
red_black_tree<Key, Value>::red_black_tree() {
  root = NULL;
}

template <typename Key, typename Value>
red_black_tree<Key, Value>::red_black_tree(const vector<std::pair<Key, Value>> &vec) {
  root = NULL;
  for(auto &element : vec){
    this->insert(element);
  }
}

template <typename Key, typename Value>
red_black_tree<Key, Value>::red_black_tree(const vector<Key> &vec) {
  root = NULL;
  for (auto &element : vec) {
    this->insert(element);
  }
}
template <typename Key, typename Value>
red_black_tree<Key, Value>::~red_black_tree() {
  deleteTree(root);
}

template <typename Key, typename Value>
void red_black_tree<Key, Value>::insert(const Key &key) {
  // we call the default constructor of type Value
  insert(std::pair<Key, Value>(key, Value()));
}
/*
template <typename Key, typename Value>
void red_black_tree::insert(const Key &key, const Value &val) {
  insert(std::pair(key, val));
}
*/
template <typename Key, typename Value>
void red_black_tree<Key, Value>::insert(const std::pair<Key, Value> &element) {
  // all insertNode's color will be set as red
  auto *insertNode = new Node<Key, Value>(element.first, element.second, RED);
  root = insert(root, insertNode);
  root->color = BLACK;
}

template <typename Key, typename Value>
void red_black_tree<Key, Value>::remove(const Key &key) {
  if(isempty()) {
    std::cout << "You cannot remove element from an empty tree" << std::endl;
    return;
  }

  root = remove(root, key);
  if(!isempty())
    root->color = BLACK;
}

template <typename Key, typename Value>
void red_black_tree<Key, Value>::removeMax() {
  if(isempty()){
    std::cout << "You cannot remove max element from an empty tree" << std::endl;
    return;
  }

  root = removeMax(root);

  if(!isempty())
    root->color = BLACK;
}

template <typename Key, typename Value>
void red_black_tree<Key, Value>::removeMin() {
  if(isempty()) {
    std::cout << "You cannot remove min element from an empty tree" << std::endl;
    return;
  }

  root = removeMin(root);

  if(!isempty())
    root->color = BLACK;
}

template <typename Key, typename Value>
json red_black_tree<Key, Value>::JSON() const {
  vector<json> outputTree;
  // this queue is used to help us
  // implement the level order traverse
  queue<Node<Key, Value>*> q;
  Node<Key, Value> *temp = root;

  while(temp != NULL) {
    outputTree.push_back(printNode(temp));

    if(temp->left != NULL)
      q.push(temp->left);
    if(temp->right != NULL)
      q.push(temp->right);

    if(q.empty())
      break;
    else {
      temp = q.front();
      q.pop();
    }
  }

  return json(outputTree);
}

/*
 * Private function after this line
 */

template <typename Key,typename Value>
Node<Key, Value>* red_black_tree<Key, Value>::rotateLeft(Node<Key, Value> *root) {
  //first exchange the position of root
  // and its right child
  Node<Key, Value> *rightChild = root->right;
  root->right = rightChild->left;
  rightChild->left = root;

  rightChild->color = root->color;
  root->color = RED;
  rightChild->height = height(root);
  root->height = 1 + std::max(height(root->left), height(root->right));
  return rightChild; // rightChild is new root for this subtreee
}

template <typename Key, typename Value>
Node<Key, Value>* red_black_tree<Key, Value>::rotateRight(Node<Key, Value> *root) {
  // exchange the position of root
  // and its left child
  Node<Key, Value> *leftChild = root->left;
  root->left = leftChild->right;
  leftChild->right = root;

  leftChild->color = root->color;
  root->color = RED;
  leftChild->height = height(root);
  root->height = 1 + std::max(height(root->left), height(root->right));
  return leftChild;
}

template <typename Key, typename Value>
void red_black_tree<Key, Value>::flipColors(Node<Key, Value> *root) {
  // flipColors move mid node of 4-node to its parents node
  // if its parents are also 4-node after moving, we continue doing
  // this until parents node are 3-node after moving or we reach the
  // root, where we break 4-node into three 2-nodes
  root->color = RED;
  root->left->color = BLACK;
  root->right->color = BLACK;
}

template <typename Key, typename Value>
int red_black_tree<Key, Value>::height(Node<Key, Value> *root) const {
  if(root == NULL)
    return -1;
  return root->height;
}

template <typename Key, typename Value>
void red_black_tree<Key, Value>::deleteTree(Node<Key, Value> *root) {
  if(!root)
    return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

template <typename Key, typename Value>
Node<Key, Value>* red_black_tree<Key, Value>::insert(Node<Key, Value> *node, Node<Key, Value> *insertNode) {
  // if root is NULL we return the insertNode
  // this is the basic case of this recursion
  if(node == NULL) return insertNode;

  // this is using recursion to implement BST insert
  if(insertNode->key < node->key)
    node->left = insert(node->left, insertNode);
  else if(insertNode->key > node->key)
    node->right = insert(node->right, insertNode);
  else{
    node->val = insertNode->val;
    delete insertNode;
  }

  if(isRed(node->right) && !isRed(node->left))
    node = rotateLeft(node);
  if(isRed(node->left) && isRed(node->left->left))
    node = rotateRight(node);
  if(isRed(node->left) && isRed(node->right))
    flipColors(node);

  node->height = 1 + std::max(height(node->left), height(node->right));
  return node;
}

template<typename Key, typename Value>
json red_black_tree<Key, Value>::printNode(Node<Key, Value> *node) const {
  json output;
  output["Key"] = node->key;
  output["Color"] = (node->color == RED) ? "Red" : "Black";

  if(node->left != NULL)
    output["LeftChildKey"] = node->left->key;
  else
    output["LeftChildKey"] = "NULL";

  if(node->right != NULL)
    output["RightChildKey"] = node->right->key;
  else
    output["RightChildKey"] = "NULL";

  output["Height"] = height(node);

  return output;
}

template <typename Key, typename Value>
Node<Key, Value>* red_black_tree<Key, Value>::remove(Node<Key, Value> *node, const Key &key) {
  if(key == node->key) {
    if(node->right) {
      auto tmp = node->right;
      while (tmp->left != NULL) tmp = tmp->left;
      swapNode(node, tmp);
      return removeMin(node);
    } else {
      auto tmp = node->left;
      if(tmp)
        tmp->color = node->color;
      delete node;
      return tmp; // return whatever is on node->right
    }
  }

  if(key < node->key) {
    //Move to the leftest node of the 3-node or 4-node
    if(isRed(node->left))
      node->left = remove(node->left, key);
    else {
      if (isTwoNode(node->left)) {
        // in this situation
        // node->right will not be NULL
        if (!isTwoNode(node->right))
          node = redLeftChild(node);// if its immediate sibling is not 2-node
        else
          node = combineParentAndChild(node);// if both of node's childs is 2-node
      }
      node->left = remove(node->left, key);
    }
  } else if(key > node->key) {

    if(isRed(node->left))
      node = rotateRight(node);
    if(isRed(node->right))
      node->right = remove(node->right, key);
    else {
      if(!isTwoNode(node->right)) {
        // if the right child is already 3-node
        // we simply rotate it right
        node->right = rotateRight(node->right);
      } else if(!isTwoNode(node->left)) {
        // if the right child is 2-node
        // but its immediate simbling is 3-node
        // we call the fct redRightChild
        node = redRightChild(node);
      } else {
        // if both the left and the right child are 2-nodes
        // we combine three 2-node into 4-node and move forward
        node = combineParentAndChild(node);
      }

      node->right = remove(node->right, key);
    }
  }

  return rebalanceTree(node);
}

template <typename Key, typename Value>
Node<Key, Value>* red_black_tree<Key, Value>::removeMin(Node<Key, Value> *node) {
  // node will be not NULL
  // since we already test whether the tree is
  // empty at the beginning

  //Base case
  if(node->left == NULL) {
    delete node;
    return NULL;
  }

  //Move to the leftest node of the 3-node or 4-node
  if(isRed(node->left))
    node->left = removeMin(node->left);
  else {
    if (isTwoNode(node->left)) {
      // in this situation
      // node->right will not be NULL
      if (!isTwoNode(node->right))
        node = redLeftChild(node);// if its immediate sibling is not 2-node
      else
        node = combineParentAndChild(node);// if both of node's childs is 2-node
    }

    node->left = removeMin(node->left);
  }

  return rebalanceTree(node);
}

template <typename Key, typename Value>
Node<Key, Value>* red_black_tree<Key, Value>::removeMax(Node<Key, Value> *node) {
  /*
   * this is the special situation when deleting max from a red black tree
   * if parent's left child node is red but parent->left->left is not red
   * it will call combineParentAndChilde, which is wrong in this situation
   */
  if(isRed(node->left))
    node = rotateRight(node);
  //Base case
  if(node->right == NULL) {
    delete node;
    return NULL;
  }

  if(isRed(node->right))
    node->right = removeMax(node->right);
  else {
    if(!isTwoNode(node->right)) {
      // if the right child is already 3-node
      // we simply rotate it right
      node->right = rotateRight(node->right);
    } else if(!isTwoNode(node->left)) {
      // if the right child is 2-node
      // but its immediate simbling is 3-node
      // we call the fct redRightChild
      node = redRightChild(node);
    } else {
      // if both the left and the right child are 2-nodes
      // we combine three 2-node into 4-node and move forward
      node = combineParentAndChild(node);
    }

    node->right = removeMax(node->right);
  }

  return rebalanceTree(node);
}

template <typename Key, typename Value>
void red_black_tree<Key, Value>::swapNode(Node<Key, Value> *node1, Node<Key, Value> *node2) {
  // we only swap their key and value and
  // keep their height, color unchanged
  Key node1_Key = node1->key;
  Value node1_Value = node1->val;
  node1->key = node2->key;
  node1->val = node2->val;
  node2->key = node1_Key;
  node2->val = node1_Value;
}

template <typename Key, typename Value>
bool red_black_tree<Key, Value>::isRed(Node<Key, Value> *node) const {
  // the null node is viewed as BLACK node
  if(node == NULL)
    return BLACK;
  return node->color;
}

template <typename Key, typename Value>
bool red_black_tree<Key, Value>::isTwoNode(Node<Key, Value> *node) const {
  return !isRed(node->left);
}

template <typename Key, typename Value>
Node<Key, Value>* red_black_tree<Key, Value>::redLeftChild(Node<Key, Value> *node) {
  /*
   * this function will only be called when all the following conditions are satisfied
   * 1, parent is red (except when it calls at root)
   * 2, the right child of parent is 3-node
   * 3, the left child of parent is 2-node
   */
  node->right = rotateRight(node->right);
  node = rotateLeft(node);
  node->left->color = BLACK; // this code seems unnecessary (no! because rotateLeft will color node->left RED)
  node->right->color = BLACK;
  node->left->left->color = RED;
  return node;
}

template <typename Key, typename Value>
Node<Key, Value>* red_black_tree<Key, Value>::combineParentAndChild(Node<Key, Value> *node) {
  /*
   * Assume node->color is RED
   * and both of its childs is 2-node
   */
  node->color = BLACK;
  node->left->color = RED;
  node->right->color = RED;
  return node;
}

template <typename Key, typename Value>
Node<Key, Value>* red_black_tree<Key, Value>::redRightChild(Node<Key, Value> *node) {
  /*
   * this function will only be called when all the following conditions are satisfied
   * 1, parent is red (except when it calls at root)
   * 2, the right child of parent is 2-node
   * 3, the left child of parent is 3-node
   */
  node = rotateRight(node);
  node->right->color = BLACK;
  node->left->color = BLACK;
  node->right->right->color = RED;
  return node;
}

template <typename Key, typename Value>
Node<Key, Value>* red_black_tree<Key, Value>::rebalanceTree(Node<Key, Value> *node) {
  // when we move up,
  // we need to recover right-leaning 3-nodes
  // and those 4-nodes
  if(isRed(node->right)) {
    if(isRed(node->left))
      flipColors(node);
    else
      node = rotateLeft(node);
  }
  node->height = 1 + std::max(height(node->left), height(node->right));
  return node;
}
#endif //RED_BLACK_TREE_RED_BLACK_TREE_H
