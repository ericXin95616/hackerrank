//
// Created by xinbochao on 18-5-16.
//

#ifndef SPLAY_TREE_SPLAY_TREE_H
#define SPLAY_TREE_SPLAY_TREE_H
#include <vector>
#include <utility>
#include <queue>
#include <iostream>
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
  int height; // height of the tree, the height of single
  // Node is 0

  Node(const Key &key, const Value &val):
      key(key), val(val) {
    left = NULL;
    right = NULL;
    height = 0;
  }
};

template <typename Key, typename Value>
class Splay_Tree{
 public:
  Splay_Tree();

  std::pair<Key, Value> search(const Key& key);
  void insert(const Key &key);
  void insert(const std::pair<Key, Value> &element);
  void remove(const Key &key);
  void removeMin();
  void removeMax();

  bool isempty() const {return root == NULL;}
  json JSON() const; // transform splay tree to json
  ~Splay_Tree();

 private:
  Node<Key, Value>* rotateLeft(Node<Key, Value>* node);
  Node<Key, Value>* rotateRight(Node<Key, Value>* node);
  Node<Key, Value>* splay(Node<Key, Value> *node, const Key &key);
  Node<Key, Value> *insert(Node<Key, Value> *node, const Key &key, const Value &val);
  int Height(Node<Key, Value>* node) const;
  json printNode(Node<Key, Value> *node) const;
  void deleteTree(Node<Key, Value> *root);

  Node<Key, Value>* root;
};

template <typename Key, typename Value>
Splay_Tree<Key, Value>::Splay_Tree() {
  root = NULL;
}

template <typename Key, typename Value>
std::pair<Key, Value> Splay_Tree<Key, Value>::search(const Key &key) {
  // move search key to the root(if key exists)
  splay(root, key);
  if(root->key != key) {
    //TODO: throw an exception
    std::cout << "Fail to find the key " << key << std::endl;
    return std::pair<Key, Value>();
  }
  return std::pair<Key, Value>(root->key, root->val);
}

template <typename Key, typename Value>
void Splay_Tree<Key, Value>::insert(const Key &key) {
  insert(std::pair(key, Value()));
}

template <typename Key, typename Value>
void Splay_Tree<Key, Value>::insert(const std::pair<Key, Value> &element) {
  // we first perform standard BST insert
  // then we splay the key we just add
  root = insert(root, element.first, element.second);
}

template <typename Key, typename Value>
void Splay_Tree<Key, Value>::removeMin() {
  
}

template <typename Key, typename Value>
void Splay_Tree<Key, Value>::removeMax() {

}

template <typename Key, typename Value>
void Splay_Tree<Key, Value>::remove(const Key &key) {

}

template <typename Key, typename Value>
json Splay_Tree<Key, Value>::JSON() const {
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

template <typename Key, typename Value>
Splay_Tree<Key, Value>::~Splay_Tree() {
  deleteTree(root);
}

// Private function after this line


template <typename Key, typename Value>
Node<Key, Value> * Splay_Tree<Key, Value>::insert(Node<Key, Value> *node, const Key &key, const Value &val) {
  if(node == NULL) {
    return new Node(key, val);
  }

  if(key < node->key)
    node->left = insert(node->left, key, val);
  else if(key > node->key)
    node->right = insert(node->right, key, val);
  else
    node->val = val;

  return splay(node, key);
}

template <typename Key, typename Value>
int Splay_Tree<Key, Value>::Height(Node<Key, Value> *node) const {
  if(!node)
    return -1; // height of null is defined as -1
  return node->height;
}

template <typename Key, typename Value>
Node<Key, Value>* Splay_Tree<Key, Value>::rotateRight(Node<Key, Value> *node) {
  // leftChild of node will be the new root
  // of this subtree
  Node<Key, Value>* leftChild = node->left;
  node->left = leftChild->right;
  leftChild->right = node;
  node->height = 1 + std::max(Height(node->left), Height(node->right));
  leftChild->height = 1 + std::max(Height(leftChild->left), Height(leftChild->right));
  return leftChild
}

template <typename Key, typename Value>
Node<Key, Value>* Splay_Tree<Key, Value>::rotateLeft(Node<Key, Value> *node) {
  // rightChild of node will be the new root
  // of this subtree
  Node<Key, Value>* rightChild = node->right;
  node->right = rightChild->left;
  rightChild->left = node;
  node->height = 1 + std::max(Height(node->left), Height(node->right));
  rightChild->height = 1 + std::max(Height(rightChild->left), Height(rightChild->right));
  return rightChild;
}

template <typename Key, typename Value>
Node<Key, Value> * Splay_Tree<Key, Value>::splay(Node<Key, Value> *node, const Key &key) {
  // this function first search key through splay tree
  // if we found the key, we rotate the tree and let the access node become
  // the root of this tree. If key doesn't exist in this tree, we let the last
  // access node become the root of this tree

  // base case
  if(node == NULL || node->key == key) return node;

  if(key < node->key) {
    if(node->left == NULL) return node;

    if(key < node->left->key) {
      //left-left case(Zig-Zig)
      node->left->left = splay(node->left->left, key);
      node = rotateRight(node); // rotateRight(Grandparent), now node is parent
    } else if(key > node->left->key){
      //left-right case(Zig-Zag)
      node->left->right = splay(node->left->right, key);
      // we dont know if node->left->right is null or not
      if(node->left->right != NULL)
        node->left = rotateLeft(node->left); // rotateLeft(Parent), now node->left is the key
    }

    // it is possible that after first rotation
    // node->left becomes NULL, in that case, we
    // simply return current node
    // this feature helps us to put the last access
    // code in root when key doesn't exist in tree
    if(node->left == NULL)
      return node;
    return node = rotateRight(node); // when key == node->left->key, this will be Zig case

  } else {
    if(node->right == NULL) return node;

    if(key < node->right->key) {
      // right-left case (Zag-Zig)
      node->right->left = splay(node->left->right, key);
      // first check if node->right->left is null
      if(node->right->left != NULL)
        node->right = rotateRight(node->right);
    } else if(key > node->right->key) {
      // right-right case (Zag-Zag)
      node->right->right = splay(node->right->right, key);
      node = rotateLeft(node); // rotateLeft(GP), no need to check NULL
    }

    if(node->right == NULL)
      return node;
    return node = rotateLeft(node); // Zag
  }
}

template<typename Key, typename Value>
json Splay_Tree<Key, Value>::printNode(Node<Key, Value> *node) const {
  json output;
  output["Key"] = node->key;

  if(node->left != NULL)
    output["LeftChildKey"] = node->left->key;
  else
    output["LeftChildKey"] = "NULL";

  if(node->right != NULL)
    output["RightChildKey"] = node->right->key;
  else
    output["RightChildKey"] = "NULL";

  output["Height"] = Height(node);

  return output;
}

template <typename Key, typename Value>
void Splay_Tree<Key, Value>::deleteTree(Node<Key, Value> *root) {
  if(!root)
    return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}
#endif //SPLAY_TREE_SPLAY_TREE_H





