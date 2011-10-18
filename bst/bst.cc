#include "bst.h"
#include "assert.h"
#include <iostream>
#include <stack>

template <class Type>
BinarySearchTree<Type>::BinarySearchTree() {
    m_path_index = 0;
    m_root = NULL;
}

template <class Type>
Type BinarySearchTree<Type>::FindMin() {
    assert(m_root);
    TreeNode traveler = m_root;
    while (NULL != traveler->m_left) {
        traveler = traveler->m_left;
    }
    return traveler->m_data;
}

template <class Type>
Type BinarySearchTree<Type>::FindMax() {
    assert(m_root);
    TreeNode traveler = m_root;
    while (NULL != traveler->m_right) {
        traveler = traveler->m_right;
    }
    return traveler->m_data;
}

template <class Type>
Node<Type>* BinarySearchTree<Type>::LL(TreeNode node) {
    TreeNode right_node = node->m_right;
    node->m_right= right_node->m_left;
    right_node->m_left = node;
    if(right_node->m_balance_factor== -1) {
        node->m_balance_factor = 0;
        right_node->m_balance_factor = 0;
    } else {
        node->m_balance_factor = -1;
        right_node->m_balance_factor = 1;
    }
#ifdef DEBUG
        std::cout << "right" << right_node->m_data << std::endl;
#endif
    return right_node;
}

template <class Type>
Node<Type>* BinarySearchTree<Type>::RR(TreeNode node) {
    TreeNode left_node = node->m_left;
    node->m_left = left_node->m_right;
    left_node->m_right = node;
    if(left_node->m_balance_factor == 1) {
        node->m_balance_factor = 0;
        left_node->m_balance_factor = 0;
    } else {
        node->m_balance_factor = 1;
        left_node->m_balance_factor = -1; 
    }
#ifdef DEBUG
        std::cout << "left" << left_node->m_data << std::endl;
#endif
    return left_node;
}

template <class Type>
Node<Type>* BinarySearchTree<Type>::RL(TreeNode node) {
    node->m_right = RR(node->m_right);
    return LL(node);
}

template <class Type>
Node<Type>* BinarySearchTree<Type>::LR(TreeNode node) {
    node->m_left = LL(node->m_left);
    return RR(node);
}

template <class Type>
void BinarySearchTree<Type>::Insert(const Type& node_value) {
    TreeNode new_node = new Node<Type>();
    std::cout << "hello" << std::endl;
    m_path_index = 0;
    new_node->m_data = node_value;
    new_node->m_balance_factor = 0;
    new_node->m_right = NULL;
    new_node->m_left = NULL;
    if(NULL == m_root) {
        m_root = new Node<Type>();
#ifdef DEBUG
        std::cout << "1" << m_root->m_data << std::endl;
#endif
        m_root = new_node;
#ifdef DEBUG
        std::cout << "1" << m_root->m_data << std::endl;
#endif
        return ;
    }
#ifdef DEBUG
    std::cout << "f2" << m_root->m_data << std::endl;
#endif
    TreeNode next_node = m_root;
    bool isLeft = true;
    while(NULL != next_node) {
        m_path[m_path_index++] = next_node;
        if(node_value < next_node->m_data) {
            next_node = next_node->m_left;
            isLeft = true;
        } else {
            next_node = next_node->m_right;
            isLeft = false;
        } 
    }
#ifdef DEBUG
    std::cout << node_value << std::endl;
#endif
    m_path_index--;
    if (isLeft)
        m_path[m_path_index]->m_left = new_node;
    else
        m_path[m_path_index]->m_right = new_node;
    int bf = 0;
    int after_bf = 2;
    TreeNode return_new_node = new Node<Type>();
#ifdef DEBUG
    std::cout << "ha" << node_value << std::endl;
#endif
    while (m_path_index>=0) {
        bf = (node_value<m_path[m_path_index]->m_data)? 1:-1;
        after_bf = 2;
        m_path[m_path_index]->m_balance_factor += bf;
        bf = m_path[m_path_index]->m_balance_factor;
#ifdef DEBUG
    std::cout << "bf" <<m_path_index << m_path[m_path_index]->m_data<< bf << std::endl;
#endif
        if (bf == 2) {
            int left_balance = m_path[m_path_index]->m_left->m_balance_factor;
            if (left_balance == 1) {
                return_new_node = RR(m_path[m_path_index]);
            } else if (left_balance == -1) {
                return_new_node = LR(m_path[m_path_index]);
            } else {
                return_new_node = RR(m_root);
            }
            after_bf = return_new_node->m_balance_factor;
        }
        if (bf == -2) {
            int right_balance = m_path[m_path_index]->m_right->m_balance_factor;
            if (right_balance == -1)
                return_new_node = LL(m_path[m_path_index]);
            else if (right_balance == 1)
                return_new_node = RL(m_path[m_path_index]);
            else
                return_new_node = LL(m_root);
            after_bf = return_new_node->m_balance_factor;
        }
        if(bf ==2 || bf ==-2) {
            if(m_path_index > 0) {
                if(m_path[m_path_index]->m_data < m_path[m_path_index-1]->m_data)
                    m_path[m_path_index-1]->m_left = return_new_node;
                else {
                    m_path[m_path_index-1]->m_right = return_new_node;
                    //std ::cout <<  
                }
            }else 
                m_root = return_new_node;
        }
        if (after_bf == 0)
            return ;
#ifdef DEBUG
    std::cout << "hb" <<m_path_index << std::endl;
#endif
        m_path_index--;
    }
#ifdef DEBUG
        std::cout << "1" << m_root->m_data << std::endl;
        //std::cout << "2" << m_root->m_right->m_data << std::endl;
        std::cout << "2" << m_root->m_left->m_data << std::endl;
#endif
}

template <class Type>
void BinarySearchTree<Type>::DeleteNode(TreeNode node) {
    TreeNode index_pointer = node;
    if (node->m_left != NULL && node->m_right != NULL) {
        index_pointer = node->m_left;
        while(index_pointer->m_right != NULL) {
            m_path[m_path_index++] = index_pointer->m_right;
            index_pointer = index_pointer->m_right;
        }
        --m_path_index;
        node->m_data = index_pointer->m_data;
        if (m_path[m_path_index] == node)
            node->m_left = index_pointer->m_left;
        else
            m_path[m_path_index]->m_right = index_pointer->m_left;
    }
    else {
        index_pointer = node->m_left;
        if (index_pointer == NULL) 
            index_pointer = node->m_right;
        --m_path_index;
        if (m_path_index > 0) {
            if (m_path[m_path_index-1]->m_left == node)
                m_path[m_path_index-1]->m_left = index_pointer;
            else
                m_path[m_path_index-1]->m_right = index_pointer;
        } 
        else 
            m_root = index_pointer;
    }//delete over
    --m_path_index; 
    while (m_path_index>=0) {
        int bf = (node->m_data < m_path[m_path_index]->m_data )? -1 : 1;
        m_path[m_path_index--]->m_balance_factor += bf;
        bf = m_path[m_path_index]->m_balance_factor;
        TreeNode return_new_node = new Node<Type>();
        if (bf != 0) {
            if (bf == 1 || bf == -1)
                break;
            if (bf == 2) {
                int left_balance = m_path[m_path_index]->m_left->m_balance_factor;
                if (left_balance == 1) {
                    return_new_node = RR(m_path[m_path_index]);
                } else if (left_balance == -1) {
                    return_new_node = LR(m_path[m_path_index]);
                } else {
                    return_new_node = RR(m_root);
                }
            }
            if (bf == -2) {
                int right_balance = m_path[m_path_index]->m_right->m_balance_factor;
                if (right_balance == -1)
                    return_new_node = LL(m_path[m_path_index]);
                else if (right_balance == 1)
                    return_new_node = RL(m_path[m_path_index]);
                else
                    return_new_node = LL(m_root);
            }   
            if (return_new_node->m_balance_factor == 0)
                return ;
            if(bf ==2 || bf ==-2) {
                if(m_path_index > 0) {
                    if(m_path[m_path_index] < m_path[m_path_index-1])
                        m_path[m_path_index-1]->m_left = return_new_node;
                    else
                        m_path[m_path_index-1]->m_right = return_new_node;
                }else 
                    m_root = return_new_node;
            }
            m_path_index--;
         }
    }
}

template <class Type>
void BinarySearchTree<Type>::Delete(const Type& node_value) {
    assert(m_root);
    m_path_index =0;
    TreeNode traveler = m_root;
    while (traveler!=NULL) {
        m_path[m_path_index++] = traveler;
#ifdef DEBUG
    std::cout << "delete1" << traveler->m_data << std::endl;
#endif
        if (traveler->m_data == node_value) {
#ifdef DEBUG
    std::cout << "delete" << traveler->m_data << std::endl;
#endif
            DeleteNode(traveler);
            return;
        }
        else if (traveler->m_data < node_value)
            traveler = traveler->m_right;
        else
            traveler = traveler->m_left;
    }
}
template <class Type>
void BinarySearchTree<Type>::InorderTraversal() {
    assert(m_root);
    std::stack<TreeNode> travel;
    TreeNode traveler = m_root;
    while(!travel.empty() || traveler!=NULL) {
        while (traveler != NULL) {
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
        if (!travel.empty()) {
            std::cout << travel.top()->m_data << std::endl;
            traveler = travel.top();
            traveler = traveler->m_right;
            travel.pop();
        }
    }
}
template <class Type>
Node<Type>* BinarySearchTree<Type>::Search(const Type& node_value) {
    assert(m_root);
    TreeNode traveler = m_root;
    while (traveler!=NULL) {
        if (traveler->m_data == node_value) {
            return traveler;
        }
        else if (traveler->m_data < node_value)
            traveler = traveler->m_right;
        else
            traveler = traveler->m_left;
    }
    return NULL;
}
template <class Type>
Type BinarySearchTree<Type>::Predecessor(const Type& node_value) {
    assert(m_root);
    m_path_index =0;
    TreeNode traveler = m_root;
    while (traveler!=NULL) {
        m_path[m_path_index++] = traveler;
        if (traveler->m_data == node_value) {
            traveler = traveler->m_left;
            m_path_index -= 2;
            if (traveler != NULL) {
                while (traveler->m_right != NULL) {
                    traveler = traveler->m_right;
                }
            } else {
                traveler = m_path[m_path_index+1];
                while (m_path_index >= 0) {
                    if (m_path[m_path_index]->m_left == traveler)
                        traveler = m_path[m_path_index--];
                    else
                        return m_path[m_path_index]->m_data;
                }
                std::cout << "gg" << std::endl;
                if (m_path_index < 0)
                    return 0;
            }
            return traveler->m_data;
        }
        else if (traveler->m_data < node_value)
            traveler = traveler->m_right;
        else
            traveler = traveler->m_left;
    }
}

template <class Type>
Type BinarySearchTree<Type>::Successor(const Type& node_value) {
    assert(m_root);
    m_path_index =0;
    TreeNode traveler = m_root;
    while (traveler!=NULL) {
        m_path[m_path_index++] = traveler;
        if (traveler->m_data == node_value) {
            traveler = traveler->m_right;
            m_path_index -= 2;
            if (traveler != NULL) {
                while (traveler->m_left != NULL) {
                    traveler = traveler->m_left;
                }
            } else {
                traveler = m_path[m_path_index+1];
                while (m_path_index >= 0) {
                    if (m_path[m_path_index]->m_right == traveler)
                        traveler = m_path[m_path_index--];
                    else
                        return m_path[m_path_index]->m_data;
                }
                if (m_path_index < 0)
                    return 0;
            }
            return traveler->m_data;
        }
        else if (traveler->m_data < node_value)
            traveler = traveler->m_right;
        else
            traveler = traveler->m_left;
    }
}
