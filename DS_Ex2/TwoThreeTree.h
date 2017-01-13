#ifndef TWOTHREETREE
#define TWOTHREETREE

#include <list>
#include "Node.h"
#include "LeafNode.h"
#include "InternalNode.h"
#include <iostream>
using  namespace std;
class Node;
class LeafNode;
class InternalNode;

class TwoThreeTree {
	
	Node *root; // root of tree
	list<LeafNode*> leaves; // list of all leaves in structure

public:
	//CTOR
	TwoThreeTree():root(nullptr){}

	//findNode: finds the leaf node with 'key', if exists
	DataType* findNode(KeyType key);

	//findParent: finds the parent of the leaf node with 'key'
	InternalNode *findParent(KeyType key);

	//findLeafWithKey: finds which one of the parent's leafs is the one with 'key', if exists
	LeafNode* findLeafWithKey(KeyType key, InternalNode* parentNode);

	//insertNode: inserts new node with 'key' and 'data' to the tree
	bool insertNode(KeyType key, DataType * data);

	//insertNodeToEmptyTree: handles the insert case when tree is empty
	bool insertNodeToEmptyTree(KeyType key, DataType* data);

	//insertNodeToOneLeafTree: handels the insert case when tree has only one leaf
	bool insertNodeToOneLeafTree(KeyType key, DataType* data);

	//insertNodeToRichTree: handels the insert case when tree has more than one leaf
	bool insertNodeToRichTree(KeyType key, DataType* data);

	//bool deleteNode(Node *toInsert);

	//createInternalWith4Children: creates array of 4 nodes, ordered by their keys
	Node** createInternalWith4Children(InternalNode* parent, Node* newChild, KeyType keyChild);

	//splitChildrenAndAddToTree: splits array of 4 nodes to 2 internal nodes, then inserts them to the tree
	void splitChildrenAndAddToTree(Node** array4sons, KeyType* array4keys, InternalNode* parentNode);

	void print();

	void printKeynotFound() const{
		cout <<"Key wasn't found\n";
	}

	void printKeyExists(bool exists) const {
		if (exists)
			cout << "Key already exist\n";
		else
			cout << "Key does not exist\n";
	}


	//TODO: we need to add destructor to kill all the students. kiil them. kill them all.
};


#endif
