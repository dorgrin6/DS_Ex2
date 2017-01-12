#ifndef _INTERNAL_NODE_H_
#define _INTERNAL_NODE_H_

#include "Node.h"

class InternalNode : public Node {
	Node *left, *mid, *right;
	int min1,min2, min3;
	friend class TwoThreeTree;

public:
	InternalNode(Node* _left = nullptr, Node* _mid = nullptr, Node* _right = nullptr,int _min1=0, int _min2 = 0, int _min3 = 0)
		:left(_left), mid(_mid), right(_right),min1(_min1), min2(_min2), min3(_min3) {}

	virtual void print()const{}


	bool hasRight() const {
		return (right != nullptr);
	}
};

#endif
