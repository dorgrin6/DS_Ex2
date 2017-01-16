
#ifndef _NODE_H_
#define _NODE_H_

#include "Student.h"

class LeafNode;
class InternalNode;
typedef int KeyType;
typedef Student DataType;
#define emptyKey 0 



class Node {
	Node *parent;

	friend class TwoThreeTree;
public:
	//CTOR
	Node(Node* _parent = nullptr) :parent(_parent) {}

	//isLeaf: returns 'true' if node is leaf, 'false' else
	virtual bool isLeaf() const = 0;

	//isInternal: returns 'true' if node is internal, 'false' else
	virtual bool isInternal() const = 0;
	
	//print: print the data of node (only if he's a leaf)
	virtual void print()const = 0;

	//asLeaf: cast a node to LeafNode
	LeafNode* asLeaf();

	//asInternal: cast a node to InternalNode
	InternalNode* asInternal();
};
#endif



