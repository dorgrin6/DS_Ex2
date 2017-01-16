#ifndef TWOTHREETREE
#define TWOTHREETREE

#include <list>
#include "Node.h"
#include "LeafNode.h"
#include "InternalNode.h"
#include <iostream>
using  namespace std;
typedef list<LeafNode*>::iterator leavesIter;


class Node;
class LeafNode;
class InternalNode;

class TwoThreeTree {
	
	Node *root; // root of tree
	list<LeafNode*> leaves; // list of all leaves in structure

public:
	//CTOR
	TwoThreeTree() :root(nullptr) {}

	//findNode: finds the leaf node with 'key', if exists
	DataType* findNode(KeyType key);

	//insertNode: inserts new node with 'key' and 'data' to the tree
	bool insertNode(KeyType key, DataType * data);

	//deleteNode: deletes the leaf with 'key' from the tree
	bool deleteNode(KeyType key);


	//print: prints leaves list
	void print();

	//print: prints whether key exists
	void printKeyExists(bool exists) const {
		if (exists)
			cout << "Key already exists\n";
		else{
			cout << "Key does not exist\n";
		}
	}

	//DTOR
	~TwoThreeTree() {
		delete root;
	}

private:
	//----------------------------------LIST FUNCTIONS----------------------------------
	//listInsertBefore: inserts node before iterator it in leaves list
	void listInsertBefore(LeafNode * node, leavesIter it);
	
	//listInsertAfter: inserts node after iterator it in leaves list
	void listInsertAfter(LeafNode * node, leavesIter it);

	//listInsertToBeginning: inserts node at the beginning of leaves list
	void listInsertToBeginning(LeafNode* node);
	
	
	//----------------------------------INSERT FUNCTIONS----------------------------------
	//insertNodeToEmptyTree: handles the insert case when tree is empty
	bool insertNodeToEmptyTree(KeyType key, DataType* data);

	//insertNodeToOneLeafTree: handles the insert case when tree has only one leaf
	bool insertNodeToOneLeafTree(KeyType key, DataType* data);

	//insertNodeToRichTree: handles the insert case when tree has more than one leaf
	bool insertNodeToRichTree(KeyType key, DataType* data);

	//insertLeafToParentWith2Leaves: handles the insert of new leaf to a parent with 2 leaves
	void insertLeafToParentWith2Leaves(InternalNode* parentNode, LeafNode* newLeaf);

	//insertLeafToParentWith3Leaves: handles the insert of new leaf to a parent with 3 leaves
	void insertLeafToParentWith3Leaves(InternalNode* parentNode, LeafNode* newLeaf);

	//createInternalWith4Children: creates array of 4 nodes, ordered by their keys
	Node** createInternalWith4Children(InternalNode* parent, Node* newChild, KeyType keyChild, int &childIndex);

	//splitChildrenAndAddToTree: splits array of 4 nodes to 2 internal nodes, then inserts them to the tree
	void splitChildrenAndAddToTree(Node** array4sons, KeyType* array4keys, InternalNode* parentNode);

	//attachSonsToParent: attach 2 sons from array to parentNode
	void attachSonsToParent(InternalNode* parentNode, Node** array4sons, KeyType* array4keys);

	//updateMin1FromParentToRoot: updates min1 from the parent up to the root of the tree, if needed
	void updateMin1FromParentToRoot(InternalNode* parentNode, KeyType oldMin1, KeyType newMin1);

	//----------------------------------DELETE FUNCTIONS----------------------------------

	//deleteNodeFromEmptyTree: handles the delete if the tree is empty
	bool deleteNodeFromEmptyTree(KeyType key);

	//deleteNodeFromOneLeafTree:handles the delete if the tree is one leaf
	bool deleteNodeFromOneLeafTree(KeyType key);

	//deleteNodeFromRichTree: handles the delete if the tree has more than one leaf
	bool deleteNodeFromRichTree(KeyType key);

	//deleteLeafFromParentWith2Leaves: handles the delete of leaf with 'key' if it's parent has 2 leaves
	void deleteLeafFromParentWith2Leaves(InternalNode* parentNode, KeyType key);

	//deleteLeafFromParentWith3Leaves: handles the delete of leaf with 'key' if it's parent has 3 leaves
	void deleteLeafFromParentWith3Leaves(InternalNode* parentNode, KeyType key);

	//resolveParentWithOneChild: handles parent who has only 1 child
	void resolveParentWithOneChild(InternalNode* parentNode);

	//resolveParentWithOneChildIsRight: handles parent who has only 1 child, and he is the 'right' of grandParent
	void resolveParentWithOneChildIsRight(InternalNode* parentNode, InternalNode* grandParent);

	//resolveParentWithOneChildIsMid: handles parent who has only 1 child, and he is the 'mid' of grandParent
	void resolveParentWithOneChildIsMid(InternalNode* parentNode, InternalNode* grandParent);

	//resolveParentWithOneChildIsLeft: handles parent who has only 1 child, and he is the 'left' of grandParent
	void resolveParentWithOneChildIsLeft(InternalNode* parentNode, InternalNode* grandParent);

	//----------------------------------FIND FUNCTIONS----------------------------------
	//findParent: finds the parent of the leaf node with 'key'
	InternalNode *findParent(KeyType key);

	//findLeafWithKey: finds which one of the parent's leafs is the one with 'key', if exists
	LeafNode* findLeafWithKey(KeyType key, InternalNode* parentNode);

};


#endif
