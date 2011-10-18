#include "cplusplus.h"
#include <queue>


void Bplusplus::Create() {
	root = new BTNode();
}

Bplusplus::Bplusplus() {
	Create();
}

void Bplusplus::Split(PBTNode parent, int childIndex, PBTNode child) {
	/**
	*parent:		父亲节点
	*childIndex：	父亲节点中key所在索引
	*child:			child = parent->childs[childIndex],是需要进行拆分的节点
	*child是满的子节点，而parent是不满的节点，首先将child拆分成两个子节点，每一子节点的大小为MaxKeys,
	*然后将中间的key，提升到parent中，并将新拆分的子节点加入到parent的childs中。
	*/
	PBTNode newNode = new BTNode();
	newNode->hasLeaf = child->hasLeaf;
	newNode->numKeys = MaxKeys;
	for (int i=0; i<MaxKeys; i++) {						//将child节点中的后MaxKeys个keys和values插入到新建的饿节点中
		newNode->keys[i] = child->keys[MaxKeys+1+i];
		newNode->values[i] = child->values[MaxKeys+1+i];
	}
	if (!child->hasLeaf) {								//如果child是子节点，没有必要将该节点childs剪切到新节点
		for (int j=0; j<MaxKeys+1; ++j) {
			newNode->childs[j] = child->childs[j+MaxKeys+1];
		}
	}
	child->numKeys = MaxKeys;

	for (int k=2*MaxKeys; k>childIndex; --k) {			//parent顺次移位，为提上来的key空位置
		parent->keys[k] = parent->keys[k-1];
		parent->values[k] = parent->values[k-1];
	}
	parent->keys[childIndex] = child->keys[MaxKeys];
	parent->values[childIndex]  = child->values[MaxKeys];
	parent->numKeys++;
	for (int k=2*MaxKeys+1; k>childIndex+1; --k) {		//在parent中添加新建的子节点
		parent->childs[k] = parent->childs[k-1];
	}
	parent->childs[childIndex+1] = newNode;
}

void Bplusplus::Insert(Tkey key, Tvalue value) {
	PBTNode child = root;
	if (root->numKeys == 2*MaxKeys+1) {			//如果根节点是满的，这是需要新建一个节点作为根节点，然后拆分、插入。
		PBTNode newNode = new BTNode();
		newNode->hasLeaf = false;
		newNode->numKeys = 0;
		newNode->childs[0] = root;
		root = newNode;
		Split(root,0,child);
		InsertNonFull(root,key,value);
	} else {
		InsertNonFull(root,key,value);
	} 
}

void Bplusplus::InsertNonFull(PBTNode parent, Tkey key, Tvalue value) {
	/**
	*将key和value插入到节点中。
	*首先判断该节点是否为叶子节点，如果是，则直接插入，完毕。
	*如果不是叶子节点，找到所在的子节点，判断是否满，满：拆分，拆分之后，判断key具体在那个新的子节点中，递归
	**/
	int num = parent->numKeys-1;
	if (parent->hasLeaf) {
		while (num>=0 && key<parent->keys[num]) {
			parent->keys[num+1] = parent->keys[num];
			parent->values[num+1] = parent->values[num];
			num--;
		}
		parent->keys[num+1] = key;
		parent->values[num+1] = value;
		parent->numKeys++;
	} else {
		while (num>=0 && key<parent->keys[num]) {
			num--;
		};
		num++;
		PBTNode newNode = parent->childs[num];
		if (newNode->numKeys == 2*MaxKeys+1) {
			Split(parent,num,newNode);
			if (key > parent->keys[num])
				num++;
		}
		InsertNonFull(parent->childs[num],key,value);
	}
}

void Bplusplus::Show(PBTNode newNode) {
	/*将所有的叶子节点输出
	std::queue<PBTNode> queue;
	if (NULL!=root) {
		queue.push(root);
		while(!queue.empty()) {
			PBTNode newNode = queue.front();
			queue.pop();
			if (newNode->hasLeaf) {
				for (int i=0; i<newNode->numKeys; ++i)
					std::cout << newNode->values[i] << std::endl;
			} else {
				for (int i=0; i<newNode->numKeys+1; ++i)
					queue.push(newNode->childs[i]);
			}
		}
	}
	*/
	/*
	*采用递归的方式输出B树的值
	*/
	if (NULL == newNode)
		return;
	for (int i=0; i<newNode->numKeys; ++i) {
		Show(newNode->childs[i]);
		std::cout << newNode->values[i] << std::endl;
	}
	Show(newNode->childs[newNode->numKeys]);
}

void Bplusplus::Show() {
	Show(root);
}

int Bplusplus::isKeyInNode(PBTNode pNode, Tkey key) {
	//判断key是否在该节点中
	for (int i=0; i<pNode->numKeys; ++i) {
		if (key == pNode->keys[i])
			return i+1;
	}
	return 0;
}

void Bplusplus::DeleteKeyInLeafNode(PBTNode pNode, int keyIndex) {
	pNode->numKeys--;
	for (int i=keyIndex; i<pNode->numKeys; ++i) {
		pNode->keys[i] = pNode->keys[i+1];
		pNode->values[i] = pNode->values[i+1];
	}
}

void Bplusplus::MergeNodes(PBTNode pNode1, Tkey key, Tvalue value, PBTNode pNode2) {
	pNode1->keys[pNode1->numKeys] = key;
	pNode1->values[pNode1->numKeys] = value;
	pNode1->numKeys++;
	int i=0;
	for (; i<pNode2->numKeys; ++i) {
		pNode1->keys[pNode1->numKeys+i] = pNode2->keys[i];
		pNode1->values[pNode1->numKeys+i] = pNode2->values[i];
		pNode1->childs[pNode1->numKeys+i] = pNode2->childs[i];
	}
	pNode1->numKeys += pNode2->numKeys;
	pNode1->childs[pNode1->numKeys] = pNode2->childs[i];
}

PBTNode Bplusplus::Recuision(PBTNode pNode, Tkey key) {
	/*
	*如果key不在pNode中，则一直递归调用，直到找到key所在的节点
	*如果该节点的keys个数大于maxkeys，则递归调用。
	*如果小于等于maxkeys，需要看左右的兄弟节点，如果左右的兄弟节点有一个节点的keys格式大于maxkeys，
	*则将该节点的一个关键字，提到父亲节点，将父亲节点的关键字下移到该节点，对该节点进行递归。
	*如果都小于等于maxkeys，则进行合并，对新的节点进行递归
	*/
	if (!isKeyInNode(pNode,key)) {
		int childIndex = pNode->numKeys-1;
		while (childIndex>=0 && key<pNode->keys[childIndex])
			childIndex--;
		childIndex++;
		PBTNode childNode = pNode->childs[childIndex];
		if (pNode->childs[childIndex]->numKeys <= MaxKeys) {
			if (childIndex>0 && pNode->childs[childIndex-1]->numKeys>MaxKeys) {
				pNode->childs[childIndex]->childs[pNode->childs[childIndex]->numKeys+1] = pNode->childs[childIndex]->childs[pNode->childs[childIndex]->numKeys];
				for (int i=pNode->childs[childIndex]->numKeys; i>0; --i) {
					pNode->childs[childIndex]->keys[i] = pNode->childs[childIndex]->keys[i-1];
					pNode->childs[childIndex]->values[i] = pNode->childs[childIndex]->values[i-1];
					pNode->childs[childIndex]->childs[i] = pNode->childs[childIndex]->childs[i-1];
				}
				pNode->childs[childIndex]->keys[0] = pNode->keys[childIndex-1];
				pNode->childs[childIndex]->values[0] = pNode->values[childIndex-1];
				pNode->childs[childIndex]->childs[0] = pNode->childs[childIndex-1]->childs[pNode->childs[childIndex-1]->numKeys];
				pNode->keys[childIndex-1] = pNode->childs[childIndex-1]->keys[pNode->childs[childIndex-1]->numKeys-1];
				pNode->values[childIndex-1] = pNode->childs[childIndex-1]->values[pNode->childs[childIndex-1]->numKeys-1];
				pNode->childs[childIndex-1]->numKeys--;
			} else if (childIndex<pNode->numKeys && pNode->childs[childIndex+1]->numKeys>MaxKeys) {
				pNode->childs[childIndex]->keys[pNode->childs[childIndex]->numKeys] = pNode->keys[childIndex];
				pNode->childs[childIndex]->values[pNode->childs[childIndex]->numKeys] = pNode->values[childIndex];
				pNode->childs[childIndex]->childs[pNode->childs[childIndex]->numKeys+1] = pNode->childs[childIndex+1]->childs[0];
				pNode->keys[childIndex] = pNode->childs[childIndex+1]->keys[0];
				pNode->values[childIndex] = pNode->childs[childIndex+1]->values[0];
				pNode->childs[childIndex]->numKeys++;
				int i=0;
				for (; i<pNode->childs[childIndex+1]->numKeys-1; ++i) {
					pNode->childs[childIndex+1]->keys[i] = pNode->childs[childIndex+1]->keys[i+1];
					pNode->childs[childIndex+1]->values[i] = pNode->childs[childIndex+1]->values[i+1];
					pNode->childs[childIndex+1]->childs[i] = pNode->childs[childIndex+1]->childs[i+1];
				}
				pNode->childs[childIndex+1]->childs[i] =pNode->childs[childIndex+1]->childs[i+1];
				pNode->childs[childIndex+1]->numKeys--;
			} else {
				if (childIndex>0 && childIndex<=pNode->numKeys)
					MergeNodes(pNode->childs[childIndex-1], key,  pNode->values[childIndex-1], pNode->childs[childIndex]);
				else
					MergeNodes(pNode->childs[childIndex], key,  pNode->values[childIndex], pNode->childs[childIndex+1]);
			}
		}
		return Recuision(pNode->childs[childIndex], key);
	}
	return pNode;
}

void Bplusplus::Delete(PBTNode pNode, Tkey key) {
	if (isKeyInNode(pNode,key)) {
		int keyIndex = isKeyInNode(pNode,key)-1;
		if (pNode->hasLeaf)							//如果key在该节点中，并且节点是子节点，则直接删除key
			DeleteKeyInLeafNode(pNode,keyIndex);
		else {										//如果key在该节点中，并且节点是内节点
			if (pNode->childs[keyIndex]->numKeys > MaxKeys) {	//如果key的叶子节点的key个数至少为MaxKeys+1个
				pNode->keys[keyIndex] = pNode->childs[keyIndex]->keys[pNode->childs[keyIndex]->numKeys-1]; //将key在子节点的前驱覆盖自己
				pNode->values[keyIndex] = pNode->childs[keyIndex]->values[pNode->childs[keyIndex]->numKeys-1];
				Delete(pNode->childs[keyIndex], pNode->keys[keyIndex]);									//递归的删除子节点的key值
			} else if (pNode->childs[keyIndex+1]->numKeys > MaxKeys) {
				pNode->keys[keyIndex] = pNode->childs[keyIndex+1]->keys[0]; //将key在子节点的前驱覆盖自己
				Delete(pNode->childs[keyIndex+1], pNode->keys[keyIndex]);	
			} else {
				MergeNodes(pNode->childs[keyIndex], key, pNode->values[keyIndex], pNode->childs[keyIndex+1]);
				DeleteKeyInLeafNode(pNode,keyIndex);
				for (int i=keyIndex+1; i<pNode->numKeys; ++i) {
					pNode->childs[i] = pNode->childs[i+1];
				}
			}
		}//if else end
	} else {
		PBTNode pNewNode = Recuision(pNode, key); //找到key所在的节点
		Delete(pNewNode, key);
	}
}

void Bplusplus::Delete(Tkey key) {
	Delete(root,key);
}