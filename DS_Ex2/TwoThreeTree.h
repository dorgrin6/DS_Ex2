#ifndef TWOTHREETREE
#define TWOTHREETREE

#include <list>
#include "Node.h"
#include "LeafNode.h"
#include "InternalNode.h"
#include <iostream>
using  namespace std;
class LeafNode;
class InternalNode;

class TwoThreeTree {
	
	
	list<LeafNode*> leaves; // list of all leaves in structure
	Node *root; // root of tree


public:
	TwoThreeTree():root(nullptr){}

	bool insertNode(Node *toInsert);
	LeafNode* findLeafWithKey(int key, InternalNode* parent);
	bool deleteNode(Node *toInsert);

	DataType* findNode(int key);

	InternalNode *findParent(int key);


	LeafNode* findNodeRec(Node * root, int key);

	bool insertNode(KeyType key, DataType * data);

	void print();


};


#endif
