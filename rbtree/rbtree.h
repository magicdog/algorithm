/***********************************************
*name	:red-black tree
*author	:hanshaoteng
*time	:2011-4-7
*des	:该文件主要是实现了红黑树，采用了链表的
*		 方式实现。	
************************************************/
#ifndef RBTREE_H
#define RETREE_H
#include <cstdlib>

//定义节点的颜色，分为红色和黑色
enum NodeColor {
    BLACK = 0,
    RED
};

template <class Type>
class TreeNode {
//定义树中的节点，具体的参数说明如下：
//m_data	:节点中的数据值
//m_left	:节点的左子树
//m_right	:节点的右子树
//m_parent	:节点的父亲节点
//m_color	:节点的颜色
public:
    TreeNode() : m_left(NULL),m_right(NULL),m_parent(NULL),m_color(BLACK) {}
    Type m_data;
    TreeNode<Type>* m_left;
    TreeNode<Type>* m_right;
    TreeNode<Type>* m_parent;
    NodeColor m_color;    
};

template <class Type>
class RbTree {
public:
    typedef TreeNode<Type>* TreeRoot;
    typedef TreeNode<Type>* TreeNodePointer;
    RbTree();
    ~RbTree();
    void Insert(const Type&);
    void Delete(const Type&);
    void ShowNode(TreeNodePointer);					//根据节点的指针地址现实节点的值
    TreeNodePointer Successor(TreeNodePointer);		//返回节点后继节点的指针
    TreeNodePointer Search(const Type&);			//根据值搜索节点的指针
    void Show();									//中序输出树的值
private:
    void LeftRotate(TreeNodePointer);				//坐旋转
    void RightRotate(TreeNodePointer);				//右旋转
    void InsertFixup(TreeNodePointer);				//插入之后，调整树的颜色，使其满足红黑树
    void DeleteFixup(TreeNodePointer);				//删除之后，调整树的颜色，使其满足红黑树
    TreeRoot m_root;								//树的根指针
    TreeNode<Type> m_nil;							//相当于空指针
};
#endif
