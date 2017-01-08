#ifndef TWOTHREETREE
#define TWOTHREETREE

#include <list>
#include "TwoThreeNode.h"
using  namespace std;


class TwoThreeTree {
	list<TwoThreeNode::Student> leaves; // list of all leaves in structure
	TwoThreeNode *root; // root of tree



public:
	TwoThreeTree():root(nullptr){}
	
	void insertNode(TwoThreeNode &toInsert);

	void deleteNode(TwoThreeNode &toInsert);

	void findNode(TwoThreeNode &toFind);

	void print();


};


#endif
