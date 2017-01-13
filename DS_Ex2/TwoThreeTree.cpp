#include "TwoThreeTree.h"

bool TwoThreeTree::insertNode(KeyType key,DataType *data){
	bool res = false;

	//tree is empty
	if (root == nullptr)
		res = insertNodeToEmptyTree(key, data);

	//tree is a one leaf
	else if (root->isLeaf())
		res = insertNodeToOneLeafTree(key, data);
	
	//tree is a rich of leaves (=more than one leaf)
	else
		res = insertNodeToRichTree(key, data);

	return res;
}//insertNode

bool TwoThreeTree::insertNodeToEmptyTree(KeyType key, DataType* data) {
	root = new LeafNode(key, *data);
	return true;
}//insertNodeToEmptyTree

bool TwoThreeTree::insertNodeToOneLeafTree(KeyType key, DataType* data) {
	LeafNode *newLeaf; //holds the key and data of the new leaf
	InternalNode *newInternal; //holds the root and the new leaf, and becomes the new root

	//the new key is already exists in tree
	if (key == root->asLeaf()->key)
	{
		printKeyExists(false);
		return false;
	}

	//the new key doesnt exists already in the tree, means we need to insert it
	else
	{
		newInternal = new InternalNode();
		newLeaf = new LeafNode(key, *data);

		/* the root's key is lower than the new leaf's key
		root's leaf becomes 'left' and new leaf becomes 'mid' of the new internal node */
		if (root->asLeaf()->key < newLeaf->key) {
			newInternal->left = root;
			newInternal->mid = newLeaf;
			newInternal->min1 = root->asLeaf()->key;
			newInternal->min2 = newLeaf->key;
		}
		
		/* the root's key is higher than the new leaf's key
		root's leaf becomes 'mid' and new leaf becomes 'left' of the new internal node */
		else {
			newInternal->left = newLeaf;
			newInternal->mid = root;
			newInternal->min1 = newLeaf->key;
			newInternal->min2 = root->asLeaf()->key;
		}

		//updating leafs parent's to the new internal node
		newInternal->left->parent = newInternal;
		newInternal->mid->parent = newInternal;

		//change root to new internal node
		root = newInternal;
		return true;
	}
}//insertNodeToOneLeafTree

bool TwoThreeTree::insertNodeToRichTree(KeyType key, DataType* data) {
	InternalNode* parentNode = findParent(key); //holds the parent of the supposed new leaf
	InternalNode* tempParentNode = parentNode; //temporary holds the parent
	LeafNode *existLeaf = findLeafWithKey(key, parentNode); //holds the leaf with the same key as the new leaf, if exists
	LeafNode* newLeaf; //holds the key and data of the new leaf
	Node** array4sons; //holds all 4 children of same internal node
	KeyType* array4keys; //holds all 4 children's keys of same internal node


	//the new key is already exists in tree
	if (existLeaf != nullptr)
	{
		printKeynotFound();
		return false;
	}

	//the new key doesnt exists already in the tree, means we need to insert it
	else
	{
		newLeaf = new LeafNode(key, *data);

		//CASE 1: The parent has 2 leafs
		if (parentNode->min3 == emptyKey) {

			/* the new leaf's key is lower than the min1 of it's parent
			this is a special case because it happends ONLY when new leaf's
			key is the minimum of all the other keys in tree*/
			if (newLeaf->key < parentNode->min1) {
				parentNode->right = parentNode->mid;
				parentNode->min3 = parentNode->min2;
				parentNode->mid = parentNode->left;
				parentNode->min2 = parentNode->min1;
				parentNode->left = newLeaf;
				//updating 'min1' from parent up to the root of the tree
				do {
					parentNode->min1 = newLeaf->key;
					parentNode = parentNode->parent->asInternal();
				} while (parentNode != nullptr);
			}
			//the new leaf's key is lower than the min2 of it's parent
			else if (newLeaf->key < parentNode->min2) {
				parentNode->right = parentNode->mid;
				parentNode->min3 = parentNode->min2;
				parentNode->mid = newLeaf;
				parentNode->min2 = newLeaf->key;
			}
			//the new leaf's key is the highest in its parent
			else {
				parentNode->right = newLeaf;
				parentNode->min3 = newLeaf->key;
			}

			//updating new leaf parent's
			parentNode = tempParentNode;
			newLeaf->parent = parentNode;
		}

		//CASE 2: The parent has 3 leafs
		else {
			array4sons = createInternalWith4Children(parentNode, newLeaf, newLeaf->key);
			array4keys = new KeyType[4];
			array4keys[0] = array4sons[0]->asLeaf()->key;
			array4keys[1] = array4sons[1]->asLeaf()->key;
			array4keys[2] = array4sons[2]->asLeaf()->key;
			array4keys[3] = array4sons[3]->asLeaf()->key;
			splitChildrenAndAddToTree(array4sons, array4keys, parentNode);
		}
		return true;
	}
}//insertNodeToRichTree

Node** TwoThreeTree::createInternalWith4Children(InternalNode* parentNode, Node* newChild, KeyType keyChild) {
	Node** array4node = new Node* [4]; //array of 4 parent's children (could be leafs or internals)
	if (keyChild < parentNode->min1) {
		array4node[0] = newChild;
		array4node[1] = parentNode->left;
		array4node[2] = parentNode->mid;
		array4node[3] = parentNode->right;
	}
	else if (keyChild < parentNode->min2) {
		array4node[0] = parentNode->left;
		array4node[1] = newChild;
		array4node[2] = parentNode->mid;
		array4node[3] = parentNode->right;
	}
	else if (keyChild < parentNode->min3) {
		array4node[0] = parentNode->left;
		array4node[1] = parentNode->mid;
		array4node[2] = newChild;
		array4node[3] = parentNode->right;
	}
	else {
		array4node[0] = parentNode->left;
		array4node[1] = parentNode->mid;
		array4node[2] = parentNode->right;
		array4node[3] = newChild;
	}
	return array4node;

	//TODO: this is where we will later update the list of leafs

}//createInternalWith4Children

void TwoThreeTree::splitChildrenAndAddToTree(Node** array4sons, KeyType* array4keys, InternalNode* parentNode) {
	InternalNode* newInternal = new InternalNode();
	InternalNode* newRoot;

	//arrange lower 2 childern in parent
	parentNode->left = array4sons[0];
	parentNode->min1 = array4keys[0];
	parentNode->left->parent = parentNode;
	parentNode->mid = array4sons[1];
	parentNode->min2 = array4keys[1];
	parentNode->mid->parent = parentNode;
	parentNode->right = nullptr;
	parentNode->min3 = emptyKey;

	//arrange higher 2 children in new internal node
	newInternal->left = array4sons[2];
	newInternal->min1 = array4keys[2];
	newInternal->left->parent = newInternal;
	newInternal->mid = array4sons[3];
	newInternal->min2 = array4keys[3];
	newInternal->mid->parent = newInternal;

	delete[] array4sons;
	delete[] array4keys;

	//parentNode is the root of the tree, and we need to create a new root
	if (parentNode->parent == nullptr) 
	{
		newRoot = new InternalNode();
		newRoot->left = parentNode;
		newRoot->min1 = parentNode->min1;
		newRoot->mid = newInternal;
		newRoot->min2 = newInternal->min1;
		parentNode->parent = newRoot;
		newInternal->parent = newRoot;
		root = newRoot;
	}
	//parentNode is not the root of the tree
	else
	{
		//means parentNode have its own parent. if this parent has an empty slot 'right' we need to put the new internal node in it
		if (parentNode->parent->asInternal()->min3 == emptyKey) {
			parentNode->parent->asInternal()->right = newInternal;
			parentNode->parent->asInternal()->min3 = newInternal->min1;
			newInternal->parent = parentNode->parent;
		}
		//parent of parentNode have also 3 children, so we need to do this process all over again
		else {
			array4sons = createInternalWith4Children(parentNode->parent->asInternal(), newInternal, newInternal->min1);
			array4keys = new KeyType[4];
			array4keys[0] = array4sons[0]->asInternal()->min1;
			array4keys[1] = array4sons[1]->asInternal()->min1;
			array4keys[2] = array4sons[2]->asInternal()->min1;
			array4keys[3] = array4sons[3]->asInternal()->min1;
			splitChildrenAndAddToTree(array4sons, array4keys, parentNode->parent->asInternal());
		}	
	}
}//splitChildrenAndAddToTree



LeafNode* TwoThreeTree::findLeafWithKey(KeyType key, InternalNode* parentNode){
	
	if (parentNode->min3!=emptyKey && key == parentNode->min3) {
		return root->asInternal()->right->asLeaf();
	}
	else if (key == parentNode->min2) {
		return root->asInternal()->mid->asLeaf();
	}
	else if (key == parentNode->min1 ){
		return root->asInternal()->left->asLeaf();
	}

	return nullptr;
}//findLeafWithKey

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
			printKeynotFound();
			return nullptr;
		}
	}


	//tree has more than one leaf
	parent = findParent(key);
	keyNode = findLeafWithKey(key, parent);

	if (keyNode == nullptr){
		printKeynotFound();
		return nullptr;
	}

	return &(keyNode->data);
	
}//findNode

//assumption node is internalNode
InternalNode * TwoThreeTree:: findParent(KeyType key){
	
	Node* node = root;
	InternalNode* parent;

	do{
		parent = node->asInternal();

		if (key < parent->min2)
			node = parent->left;
		else if (parent->min3 == emptyKey || key < parent->min3)
			node = parent->mid;
		else
			node = parent->right;
	}
	while (node != nullptr && node->isInternal());

	
	return parent;
}//findParent

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
