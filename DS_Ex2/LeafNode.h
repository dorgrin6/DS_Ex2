
#ifndef _LEAF_NODE_H_
#define  _LEAF_NODE_H_
#include "Node.h"
#include <iostream>
#include <list>

class LeafNode : public Node {
	KeyType key;
	DataType data;

	list<LeafNode*>::iterator position;


	friend class TwoThreeTree;
public:

	LeafNode(KeyType _key,DataType _data):key(_key),data(_data){}


	virtual void print()const{
		cout << data;
	}

	friend ostream& operator<< (ostream& os, const LeafNode* node) {
		os << node->data;
		return os;
	}

};

#endif
