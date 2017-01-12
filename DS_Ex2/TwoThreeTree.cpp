#include "TwoThreeTree.h"

bool TwoThreeTree::insertNode(KeyType key,DataType *data){
	bool res;

	LeafNode *newLeaf;
	InternalNode *newInternal;
	InternalNode *parent;



	//tree is empty
	if (root == nullptr){
		root = new LeafNode(key,*data);
		return  true;
	}

	//tree is a leaf
	if (root->isLeaf()){
		if (key == root->asLeaf()->key){
			cout << "The key wasn't found\n";
			return false;
		}
		
		newInternal = new InternalNode();
		newLeaf = new LeafNode(key, *data);

		//left = root, mid = new
		if (root->asLeaf()->key < newLeaf->key){
			newInternal->left = root;
			newInternal->mid = newLeaf;

			newInternal->min1 = root->asLeaf()->key;
			newInternal->min2 = newLeaf->key;
		}
		//left = new, mid = root
		else{
			newInternal->left = newLeaf;
			newInternal->mid = root;

			newInternal->min1 = newLeaf->key;
			newInternal->min2 = root->asLeaf()->key;
		}

		//change root to new created node
		root = newInternal;
		return true;
	}
	else{//tree has internal nodes (more than one leaf)
		parent = findParent(key);
		newLeaf = findLeafWithKey(key, parent);
		if (newLeaf == nullptr){
			//insert node with key to tree
		}
		else{
			cout << "key was found\n";
			return false;
		}
	}
	return false;
}

LeafNode* TwoThreeTree::findLeafWithKey(KeyType key, InternalNode* parent){
	
	if (parent->right != nullptr && key == parent->min3) {
		return root->asInternal()->right->asLeaf();
	}
	else if (key == parent->min2) {
		return root->asLeaf();
	}
	else if (key == parent->min1 ){
		return root->asLeaf();
	}

	return nullptr;
}

DataType* TwoThreeTree::findNode(KeyType key){	
	InternalNode *parent;
	LeafNode* keyNode; // node with key (if exsits)

	if (root == nullptr){
		return nullptr;
	}
	

	//tree is leaf
	if (root->isLeaf()) {
		if (root->asLeaf()->key == key)
			return &(root->asLeaf()->data);
		else {
			cout << "The key wasn't found\n";
			return nullptr;
		}
	}


	//tree has more than one leaf
	parent = findParent(key);
	keyNode = findLeafWithKey(key, parent);

	if (keyNode == nullptr){
		cout << "The key wasn't found\n";
		return nullptr;
	}

	return &(keyNode->data);
	
}

//assumption node is internalNode
InternalNode * TwoThreeTree:: findParent(KeyType key){
	
	Node* node = root;
	InternalNode* parent;

	do{
		parent = node->asInternal();

		if (key < parent->min2)
			node = parent->left;
		else if (key < parent->min3)
			node = parent->mid;
		else
			node = parent->right;
	}
	while (node != nullptr && node->isLeaf());

	
	return parent;
}

/*
LeafNode* TwoThreeTree::findNodeRec(Node *root,int key){
	if (root == nullptr) {
		return nullptr;
	}
	else if (root->isLeaf()){
		return (LeafNode*)root;
	}
		
	else{
		//root is internal node
		InternalNode *inRoot = (InternalNode *)root;
		if (inRoot->right  != nullptr && key >= inRoot->min3){
			findNodeRec(->right, key);
		}
		else if (key>=inRoot->min2){
			findNodeRec(inRoot->mid, key);
		}
		else{
			findNodeRec(inRoot->left, key);
		}
	}
}

*/


void TwoThreeTree::print(){
	list<LeafNode*>::const_iterator iter;

	for (iter = leaves.begin(); iter != leaves.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;
}
