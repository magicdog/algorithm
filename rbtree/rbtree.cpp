#include "rbtree.h"
#include <stack>
#include <iostream>
#include <assert.h>
template <class Type>
RbTree<Type>::RbTree() {
    m_root = &m_nil;		//根节点的指针指向空指针
}

template <class Type>
RbTree<Type>::~RbTree() {

}

template <class Type>
void RbTree<Type>::Insert(const Type& nodevalue){
    TreeNodePointer newnode = new TreeNode<Type>();					//newnode定义为新插入的节点
    newnode->m_data = nodevalue;
    TreeNodePointer root = m_root;									//root主要负责进行遍历，辅助找到newnode的父亲节点
    TreeNodePointer newnodeparent = &m_nil;							//指向newnode的父亲节点
    while (root != &m_nil) {
		//根据比较结果，找到newnode应该插入的位置，最后root为nil,newparentnode指向newnode的父亲
        newnodeparent = root;
        if (nodevalue < root->m_data)
            root = root->m_left;
        else
            root = root->m_right;
    }
    newnode->m_parent = newnodeparent;								//设置newnode的父亲节点
    //根据父亲节点的类型，将newnode挂到父亲节点下，
	//如果为空则说明还没有节点，让跟节点直接指向新插入的节点
	//如果newnode的值比父亲节点小，根据rb性质，查到左子树。
	if (newnodeparent == &m_nil)
        m_root = newnode;
    else if (nodevalue < newnodeparent->m_data)
        newnodeparent->m_left = newnode;
    else
        newnodeparent->m_right = newnode;
	//设置newnode的左右子树，均为nil，并设置为RED
    newnode->m_left = &m_nil;
    newnode->m_right = &m_nil;
    newnode->m_color = RED;
#ifdef DEBUG
    std::cout << newnode->m_color << newnode->m_data <<m_root->m_data << std::endl;
#endif
	//进行颜色的调整
    InsertFixup(newnode);
    newnode = NULL;
}
template <class Type>
void RbTree<Type>::LeftRotate(TreeNodePointer nodepointer) {
    assert(nodepointer);
    TreeNodePointer rightnode = nodepointer->m_right;
    assert(rightnode);
    nodepointer->m_right = rightnode->m_left;
    if (rightnode->m_left != &m_nil)
        rightnode->m_left->m_parent = nodepointer;
    rightnode->m_left = nodepointer;
    rightnode->m_parent = nodepointer->m_parent;
    if (nodepointer->m_parent == &m_nil)
        m_root = rightnode;
    else if (nodepointer->m_parent->m_right == nodepointer)
        nodepointer->m_parent->m_right = rightnode;
    else
        nodepointer->m_parent->m_left = rightnode;
    nodepointer->m_parent = rightnode;
    rightnode = NULL;
}
template <class Type>
void RbTree<Type>::RightRotate(TreeNodePointer nodepointer) {
    assert(nodepointer);
    TreeNodePointer leftnode = nodepointer->m_left;
    assert(leftnode);
    nodepointer->m_left = leftnode->m_right;
    if (leftnode->m_right != &m_nil)
        leftnode->m_right->m_parent = nodepointer;
    leftnode->m_parent = nodepointer->m_parent;
    if (nodepointer->m_parent == &m_nil)
        m_root = leftnode;
    else if (nodepointer->m_parent->m_left == nodepointer)
        nodepointer->m_parent->m_left = leftnode;
    else 
        nodepointer->m_parent->m_right = leftnode;
    leftnode->m_right = nodepointer;
    nodepointer->m_parent = leftnode;
    leftnode = NULL;
}
template <class Type>
void RbTree<Type>::InsertFixup(TreeNodePointer nodepointer) {
    TreeNodePointer brothernode;
    while (nodepointer->m_parent->m_color == RED) {
        if (nodepointer->m_parent == nodepointer->m_parent->m_parent->m_left) {
            brothernode = nodepointer->m_parent->m_parent->m_right;
            if (brothernode->m_color == RED) {
                brothernode->m_color = BLACK;
                brothernode->m_parent->m_color = RED;
                nodepointer->m_parent->m_color = BLACK;
                nodepointer = brothernode->m_parent;
            } else {
                if (nodepointer->m_parent->m_right == nodepointer) {
                    nodepointer = nodepointer->m_parent;
                    LeftRotate(nodepointer);
                }
                nodepointer->m_parent->m_color = BLACK;
                nodepointer->m_parent->m_parent->m_color = RED;
                RightRotate(nodepointer->m_parent->m_parent);
            }
        } else if(nodepointer->m_parent == nodepointer->m_parent->m_parent->m_right) {
            brothernode = nodepointer->m_parent->m_parent->m_left;
            if (brothernode->m_color == RED) {
                brothernode->m_color = BLACK;
                brothernode->m_parent->m_color = RED;
                nodepointer->m_parent->m_color = BLACK;
                nodepointer = nodepointer->m_parent;
            } else {
                if (nodepointer->m_parent->m_left == nodepointer) {
                    nodepointer = nodepointer->m_parent;
                    RightRotate(nodepointer);
                }
                nodepointer->m_parent->m_color = BLACK;
                nodepointer->m_parent->m_parent->m_color = RED;
                LeftRotate(nodepointer->m_parent->m_parent);
            }
        }
        m_root->m_color = BLACK;
        brothernode = NULL;
    }
}

template <class Type>
void RbTree<Type>::Show() {
    std::stack<TreeNodePointer> travel;
    TreeNodePointer traveler = m_root;
    while(!travel.empty() || traveler!= &m_nil) {
        while (traveler != &m_nil) {
#ifdef DEBUG
        std::cout << "stack" << traveler->m_data << std::endl;
#endif
            travel.push(traveler);
            traveler = traveler->m_left;
        }
        std::cout << travel.top()->m_data << std::endl;
        traveler = travel.top();
        travel.pop();
        traveler = traveler->m_right;
        /*if (!travel.empty()) {
            std::cout << travel.top()->m_data << std::endl;
            traveler = travel.top();
            traveler = traveler->m_right;
            travel.pop();
        } 
        */       
    }   
    traveler = NULL;
}

template <class Type>
TreeNode<Type>* RbTree<Type>::Search(const Type& nodevalue) {
    TreeNodePointer traveler = m_root;
    while (traveler != &m_nil) {
        if (nodevalue == traveler->m_data)
            return traveler;
        else if (nodevalue < traveler->m_data)
            traveler = traveler->m_left;
        else
            traveler = traveler->m_right;
    }
    traveler = NULL;
    return NULL;
}

template <class Type>
TreeNode<Type>* RbTree<Type>::Successor(TreeNodePointer nodepointer) {
    if (nodepointer->m_right != &m_nil)
        return nodepointer->m_right;
    else {
        TreeNodePointer parent = nodepointer->m_parent;
        if (parent->m_left == nodepointer)
            return parent;
        else {
            while(parent!=&m_nil && parent->m_right==nodepointer) {
                nodepointer = parent;
                parent = parent->m_parent;
            }
            return parent==&m_nil? NULL:parent;
        }
    }
}

template <class  Type>
void RbTree<Type>::ShowNode(TreeNodePointer nodepointer) {
    if (NULL == nodepointer)
        std::cout << "null" << std::endl;
    std::cout << "node value: " << nodepointer->m_data << std::endl;
}

template <class Type>
void RbTree<Type>::DeleteFixup(TreeNodePointer nodepointer) {
    while (nodepointer!=&m_nil && nodepointer->m_color==BLACK) {
        if (nodepointer = nodepointer->m_parent->m_left) {
            TreeNodePointer brothernode = nodepointer->m_parent->m_right;
            if (brothernode->m_color == RED) {
                brothernode->m_color = BLACK;
                nodepointer->m_parent->m_color = RED;
                LeftRotate(nodepointer->m_parent);
                brothernode = nodepointer->m_parent->m_right;
            }
            if (brothernode->m_left->m_color == BLACK && brothernode->m_right->m_color == BLACK) {
                brothernode->m_color = RED;
                nodepointer = nodepointer->m_parent;
            } else { 
                if (brothernode->m_right->m_color == BLACK) {
                    brothernode->m_left->m_color = BLACK;
                    brothernode->m_color = RED;
                    RightRotate(brothernode);
                    brothernode = nodepointer->m_parent->m_right;
                }
                brothernode->m_color = nodepointer->m_parent->m_color;
                nodepointer->m_parent->m_color = BLACK;
                brothernode->m_right->m_color = BLACK;
                LeftRotate(nodepointer->m_parent);
                nodepointer = m_root;
            }
        }else {
            TreeNodePointer brothernode = nodepointer->m_left;
            if (brothernode->m_color == RED) {
                brothernode->m_color = BLACK;
                nodepointer->m_parent->m_color = RED;
                RightRotate(nodepointer->m_parent);
                brothernode = nodepointer->m_parent->m_left;
            }
            if (brothernode->m_left->m_color == BLACK && brothernode->m_right->m_color == BLACK) {
                brothernode->m_color = RED;
                nodepointer = nodepointer->m_parent;
            } else {
                if (brothernode->m_left->m_color == BLACK) {
                    brothernode->m_right->m_color = BLACK;
                    brothernode->m_color = RED;
                    LeftRotate(brothernode);
                    brothernode = nodepointer->m_parent->m_left;
                }
                brothernode->m_color = nodepointer->m_parent->m_color;
                nodepointer->m_parent->m_color = BLACK;
                brothernode->m_left->m_color = BLACK;
                RightRotate(nodepointer->m_parent);
                nodepointer = m_root;
            }
        }
    }
    nodepointer->m_color = BLACK;    
}

template <class Type>
void RbTree<Type>::Delete(const Type& nodevalue) {
    TreeNodePointer deletenode = Search(nodevalue);
    TreeNodePointer deletenodepointer;
    TreeNodePointer childnode;
    assert(deletenode);
    if (deletenode->m_left == &m_nil || deletenode->m_right==&m_nil)
        deletenodepointer = deletenode;
    else 
        deletenodepointer = Successor(deletenode);
    if (deletenodepointer->m_left != &m_nil)
        childnode = deletenodepointer->m_left;
    else
        childnode = deletenodepointer->m_right;
    childnode->m_parent = deletenodepointer->m_parent;
    if (deletenodepointer->m_parent == &m_nil)
        m_root = deletenodepointer;
    else if (deletenodepointer->m_parent->m_left == deletenodepointer)
        deletenodepointer->m_parent->m_left = childnode;
    else 
        deletenodepointer->m_parent->m_right = childnode;
    if (deletenodepointer != deletenode)
        deletenode->m_data = deletenodepointer->m_data;
    if (deletenode->m_color == BLACK)
        DeleteFixup(childnode);
    deletenode = NULL;
    deletenodepointer = NULL;
    childnode = NULL;
}
