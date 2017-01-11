#ifndef TWOTHREETREE
#define TWOTHREETREE

#include <list>
#include "Node.h"
#include "LeafNode.h"
using  namespace std;


class TwoThreeTree {
	list<LeafNode::Student> leaves; // list of all leaves in structure
	Node *root; // root of tree


public:
	TwoThreeTree():root(nullptr){}
	
	bool insertNode(Node *toInsert);

	bool deleteNode(Node *toInsert);

	LeafNode* findNode(int key);

	LeafNode* findNodeRec(Node * root, int key);

	void print();


};


#endif
