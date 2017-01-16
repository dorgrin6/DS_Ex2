
#ifndef _LEAF_NODE_H_
#define  _LEAF_NODE_H_
#include "Node.h"
#include <iostream>
#include <list>

class LeafNode : public Node {
	KeyType key;
	list<LeafNode*>::iterator position; // position in leaves list
	DataType data;

	friend class TwoThreeTree;
public:
	//CTOR
	LeafNode(KeyType _key,DataType _data):key(_key),data(_data){}

	//isLeaf: returns 'true' if node is leaf, 'false' else
	virtual bool isLeaf() const { return true; }

	//isInternal: returns 'true' if node is internal, 'false' else
	virtual bool isInternal() const { return false; }

	//print: prints the data inside the leaf
	virtual void print()const{
		cout << data;
	}


	friend ostream& operator<< (ostream& os, const LeafNode* node) {
		os << node->data;
		return os;
	}

	//DTOR
	virtual ~LeafNode() {}
};

#endif
