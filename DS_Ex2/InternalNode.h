#ifndef _INTERNAL_NODE_H_
#define _INTERNAL_NODE_H_

#include "Node.h"

class InternalNode : public Node {
	Node *left, *mid, *right;
	int min1,min2, min3;
	friend class TwoThreeTree;

public:
	//CTOR
	InternalNode(Node* _left = nullptr, Node* _mid = nullptr, Node* _right = nullptr,int _min1=emptyKey, int _min2 = emptyKey, int _min3 = emptyKey)
		:left(_left), mid(_mid), right(_right),min1(_min1), min2(_min2), min3(_min3) {}

	//isLeaf: returns 'true' if node is leaf, 'false' else
	virtual bool isLeaf() const { return false; }

	//isInternal: returns 'true' if node is internal, 'false' else
	virtual bool isInternal() const { return true; }

	virtual void print()const{}

};

#endif
