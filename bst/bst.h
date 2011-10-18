//author: hanshaoteng
//time:   2011-4-1
//implement the BinarySearchTree,mainly using avl
#ifndef BST_H
#define BST_H

#include <stdint.h>
#include <cstdlib>

const unsigned int kPathArrayLength = 32;
//define the struct of the Node
template <class Type>
class Node {
public:
    Node() : m_left(NULL), m_right(NULL), m_balance_factor(0) {}
    Type m_data;
    Node<Type>* m_left;
    Node<Type>* m_right;
    int16_t m_balance_factor;
};//class Node

template <class Type>
class BinarySearchTree {
public:
    typedef Node<Type>* TreeRoot;
    typedef Node<Type>* TreeNode;
    BinarySearchTree();
    Type FindMin();
    Type FindMax();
    void Insert(const Type&);
    void Delete(const Type&);
    void InorderTraversal();
    Node<Type>* Search(const Type&);
    Type Predecessor(const Type&);
    Type Successor(const Type&);
private:
    void DeleteNode(TreeNode);
    Node<Type>* LL(TreeNode);
    Node<Type>* RR(TreeNode);
    Node<Type>* LR(TreeNode);
    Node<Type>* RL(TreeNode);
    TreeNode m_path[kPathArrayLength];
    int m_path_index;
    TreeRoot m_root;
};//class BinarySearchTree
#endif  /* BST_H */
