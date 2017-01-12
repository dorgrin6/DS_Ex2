
#ifndef _NODE_H_
#define _NODE_H_

#include "Student.h"

class LeafNode;
class InternalNode;
typedef int KeyType;
typedef Student DataType;



class Node {
	Node *parent;

	friend class TwoThreeTree;
public:

	Node(Node* _parent = nullptr) :parent(_parent) {}

	
	bool isLeaf() const {
		return typeid(*this) == typeid(LeafNode);
	}
	
	virtual void print()const = 0;

	LeafNode* asLeaf();

	InternalNode* asInternal();
};
#endif



