#ifndef _INTERNAL_NODE_H_
#define _INTERNAL_NODE_H_

#include "Node.h"

enum Child {Left, Mid, Right, Empty};

class InternalNode : public Node {
	Node *left, *mid, *right;
	int min1,min2, min3; // min values of nodes in each child
	friend class TwoThreeTree;

public:
	//CTOR
	InternalNode(Node* _left = nullptr, Node* _mid = nullptr, Node* _right = nullptr,int _min1=emptyKey, int _min2 = emptyKey, int _min3 = emptyKey)
		:left(_left), mid(_mid), right(_right),min1(_min1), min2(_min2), min3(_min3) {}

	//isLeaf: returns 'true' if node is leaf, 'false' else
	virtual bool isLeaf() const { return false; }

	//isInternal: returns 'true' if node is internal, 'false' else
	virtual bool isInternal() const { return true; }

	//hasRightChild: return 'true' if InternalNode has the right child, therefore it has 3 children. 'false' else
	bool hasRightChild()const {
		return (right == nullptr ? false : true);
	}

	//hasOneChild: return 'true' if InternalNode has only one child (=the left child), 'false' else
	bool hasOneChild()const {
		if (mid == nullptr && right == nullptr)
			return true;
		else
			return false;
	}

	//print: nothing
	virtual void print()const{}

	//replaceChild: replacing the child in 'toDelete' with the child 'toReplace'
	void replaceChild(Child toDelete, Child toReplace);

	//DTOR
	virtual ~InternalNode(){
		if (left != nullptr){
			delete left;
			left = nullptr;
		}
		if (mid != nullptr){
			delete mid;
			mid = nullptr;
		}
		if (right != nullptr){
			delete right;
			right = nullptr;
		}

	}
};

#endif
