#ifndef CPLUSPLUS_H
#define CPLUSPLUS_H
#include <iostream>

static const int MaxKeys = 3;				//设置B树的度，每个节点的关键字，最少为MaxKeys，最多为2*MaxKeys+1，
											//相应的子节点数最少MaxKeys+1.最多2*MaxKeys + 2

typedef int Tvalue;
typedef int Tkey;

class BTNode {
public:
	Tkey keys[2*MaxKeys+1];					//存储该节点的keys，直接设置成最大值
	Tvalue values[2*MaxKeys+1];
	int numKeys;
	bool hasLeaf;							//标识该节点是否是子节点
	BTNode* childs[2*MaxKeys + 2];
	BTNode() : numKeys(0), hasLeaf(true) {	//在构造函数中，初始化子树的节点
		for (int i=0; i<2*MaxKeys+2; ++i)
			childs[i] = NULL;
	}
};

typedef BTNode* PBTNode;

class Bplusplus {
public:
	Bplusplus();
	void Create();										//创建一个空的B树
	void Split(PBTNode, int, PBTNode);					//第一个参数：标识父节点；第二个参数：父节点中key关键字的index；
														//第三个参数：需要拆分的子节点
	void Search(Tkey);
	void Insert(Tkey, Tvalue);
	void Show(PBTNode);
	void Show();
	void InsertNonFull(PBTNode, Tkey, Tvalue);
	void Delete(PBTNode, Tkey);
	void Delete(Tkey);
	int isKeyInNode(PBTNode, Tkey);						//返回所在的keys中的位置
	void DeleteKeyInLeafNode(PBTNode, int);				//删除子节点中的key值
	void MergeNodes(PBTNode, Tkey, Tvalue, PBTNode);	//将子节点1+父节点中的key+子节点2合并到子节点1
	PBTNode Recuision(PBTNode, Tkey);					//对节点进行递归操作，直到找到包含该key的节点
private:
	PBTNode root;
};
#endif