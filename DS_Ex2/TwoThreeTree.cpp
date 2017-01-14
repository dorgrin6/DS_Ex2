#include "TwoThreeTree.h"

//----------------------------------FIND FUNCTIONS----------------------------------

DataType* TwoThreeTree::findNode(KeyType key) {
	InternalNode *parent;
	LeafNode* keyNode; // node with key (if exsits)

	if (root == nullptr) {
		return nullptr;
	}

	//tree is leaf
	if (root->isLeaf()) {
		if (root->asLeaf()->key == key)
			return &(root->asLeaf()->data);
		else {
			printKeyExists(false);
			return nullptr;
		}
	}


	//tree has more than one leaf
	parent = findParent(key);
	keyNode = findLeafWithKey(key, parent);

	if (keyNode == nullptr) {
		printKeyExists(false);
		return nullptr;
	}

	return &(keyNode->data);

}//findNode

//assumption: node is internalNode
InternalNode * TwoThreeTree::findParent(KeyType key) {

	Node* node = root;
	InternalNode* parent;

	do {
		parent = node->asInternal();

		if (key < parent->min2)
			node = parent->left;
		else if (parent->min3 == emptyKey || key < parent->min3)
			node = parent->mid;
		else
			node = parent->right;
	} while (node != nullptr && node->isInternal());

	return parent;
}//findParent

LeafNode* TwoThreeTree::findLeafWithKey(KeyType key, InternalNode* parentNode) {
	if (parentNode->hasRightChild() && key == parentNode->min3) {
		return parentNode->right->asLeaf();
	}
	else if (key == parentNode->min2) {
		return parentNode->mid->asLeaf();
	}
	else if (key == parentNode->min1) {
		return parentNode->left->asLeaf();
	}
	return nullptr;
}//findLeafWithKey

//----------------------------------INSERT FUNCTIONS----------------------------------

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
		printKeyExists(true);
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
	LeafNode *existLeaf = findLeafWithKey(key, parentNode); //holds the leaf with the same key as the new leaf, if exists
	LeafNode* newLeaf; //holds the key and data of the new leaf

	//the new key is already exists in tree
	if (existLeaf != nullptr){
		printKeyExists(true);
		return false;
	}

	//the new key doesnt exists already in the tree, means we need to insert it
	else
	{
		newLeaf = new LeafNode(key, *data);
		//CASE 1: The parent has 2 leaves
		if (!(parentNode->hasRightChild()))
			insertLeafToParentWith2Leaves(parentNode, newLeaf);
		//CASE 2: The parent has 3 leaves
		else
			insertLeafToParentWith3Leaves(parentNode, newLeaf);
		return true;
	}
}//insertNodeToRichTree

void TwoThreeTree::insertLeafToParentWith2Leaves(InternalNode* parentNode, LeafNode* newLeaf) {
	InternalNode* tempParentNode = parentNode; //temporary holds the parent
	KeyType oldMin1, newMin1;

	/* the new leaf's key is lower than the min1 of it's parent
	this is a special case because it happends ONLY when new leaf's
	key is the minimum of all the other keys in tree*/
	if (newLeaf->key < parentNode->min1) {
		oldMin1 = parentNode->min1;
		parentNode->replaceChild(Right, Mid);
		parentNode->replaceChild(Mid, Left);
		parentNode->left = newLeaf;
		parentNode->min1 = newLeaf->key;
		newMin1 = parentNode->min1;
		//updating 'min1' from parent up to the root of the tree
		updateMin1FromParentToRoot(parentNode->parent->asInternal(), oldMin1, newMin1);
	}
	//the new leaf's key is lower than the min2 of it's parent
	else if (newLeaf->key < parentNode->min2) {
		parentNode->replaceChild(Right, Mid);
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
}//insertLeafToParentWith2Leaves

void TwoThreeTree::insertLeafToParentWith3Leaves(InternalNode* parentNode, LeafNode* newLeaf) {
	Node** array4sons; //holds all 4 children of same internal node
	KeyType* array4keys; //holds all 4 children's keys of same internal node

	array4sons = createInternalWith4Children(parentNode, newLeaf, newLeaf->key);
	array4keys = new KeyType[4];
	array4keys[0] = array4sons[0]->asLeaf()->key;
	array4keys[1] = array4sons[1]->asLeaf()->key;
	array4keys[2] = array4sons[2]->asLeaf()->key;
	array4keys[3] = array4sons[3]->asLeaf()->key;
	splitChildrenAndAddToTree(array4sons, array4keys, parentNode);
}//insertLeafToParentWith3Leaves

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

}//createInternalWith4Children

void TwoThreeTree::splitChildrenAndAddToTree(Node** array4sons, KeyType* array4keys, InternalNode* parentNode) {
	InternalNode* newInternal = new InternalNode();
	InternalNode* newRoot;

	//arrange lower 2 childern in parentNode
	attachSonsToParent(parentNode, array4sons, array4keys);
	parentNode->replaceChild(Right, Empty);

	//arrange higher 2 children in new internal node
	attachSonsToParent(newInternal, array4sons + 2, array4keys + 2);

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
		if (!(parentNode->parent->asInternal()->hasRightChild())) {
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

void TwoThreeTree::attachSonsToParent(InternalNode* parentNode, Node** array4sons, KeyType* array4keys) {
	parentNode->left = array4sons[0];
	parentNode->min1 = array4keys[0];
	parentNode->left->parent = parentNode;
	parentNode->mid = array4sons[1];
	parentNode->min2 = array4keys[1];
	parentNode->mid->parent = parentNode;
}//attachSonsToParent

void TwoThreeTree::updateMin1FromParentToRoot(InternalNode* parentNode, KeyType oldMin1, KeyType newMin1) {
	while (parentNode != nullptr) {
		if (parentNode->min1 == oldMin1) {
			parentNode->min1 = newMin1;
			parentNode = parentNode->parent->asInternal();
		}
		else if (parentNode->min2 == oldMin1) {
			parentNode->min2 = newMin1;
			parentNode = nullptr;
		}
		else {
			parentNode->min3 = newMin1;
			parentNode = nullptr;
		}
	}
}//updateMin1FromParentToRoot

//----------------------------------DELETE FUNCTIONS----------------------------------

bool TwoThreeTree::deleteNode(KeyType key) {
	bool res = false;

	//tree is empty
	if (root == nullptr)
		res = deleteNodeFromEmptyTree(key);

	//tree is a one leaf
	else if (root->isLeaf())
		res = deleteNodeFromOneLeafTree(key);

	//tree is a rich of leaves (=more than one leaf)
	else
		res = deleteNodeFromRichTree(key);

	return res;
}//deleteNode

bool TwoThreeTree::deleteNodeFromEmptyTree(KeyType key) {
	printKeyExists(false);
	return false;
}//deleteNodeFromEmptyTree

bool TwoThreeTree::deleteNodeFromOneLeafTree(KeyType key) {
	if (root->asLeaf()->key == key) {
		delete root;
		root = nullptr;
		return true;
	}
	else {
		printKeyExists(false);
		return false;
	}
}//deleteNodeFromOneLeafTree

bool TwoThreeTree::deleteNodeFromRichTree(KeyType key) {
	InternalNode* parentNode = findParent(key); //holds the parent of the supposed new leaf
	LeafNode *existLeaf = findLeafWithKey(key, parentNode); //holds the leaf with the same key as the new leaf, if exists

	//the key is not exists in tree
	if (existLeaf == nullptr) {
		printKeyExists(false);
		return false;
	}

	//the key does exist in tree
	else
	{
		//CASE 1: The parent has 3 leafs
		if (parentNode->hasRightChild())
			deleteLeafFromParentWith3Leaves(parentNode, key);

		//CASE 2: The parent has 2 leafs
		else
			deleteLeafFromParentWith2Leaves(parentNode, key);
		return true;
	}
}//deleteNodeFromRichTree

void TwoThreeTree::deleteLeafFromParentWith2Leaves(InternalNode* parentNode, KeyType key) {
	//deletes the mid
	if (key == parentNode->min2) {
		delete parentNode->mid;
		parentNode->replaceChild(Mid, Empty);
		if (parentNode->hasOneChild())
			resolveParentWithOneChild(parentNode);
	}
	//deletes the left
	else {
		delete parentNode->left;
		parentNode->replaceChild(Left, Mid);
		parentNode->replaceChild(Mid, Empty);
		if (parentNode->hasOneChild())
			resolveParentWithOneChild(parentNode);
	}
}//deleteLeafFromParentWith2Leaves

void TwoThreeTree::deleteLeafFromParentWith3Leaves(InternalNode* parentNode, KeyType key) {
	KeyType oldMin1, newMin1;

	//deletes the right
	if (key == parentNode->min3) {
		delete parentNode->right;
		parentNode->replaceChild(Right, Empty);
	}

	//deletes the mid
	else if (key == parentNode->min2) {
		delete parentNode->mid;
		parentNode->replaceChild(Mid, Right);
		parentNode->replaceChild(Right, Empty);
	}

	//deletes the left
	/* this is a special case because it means the min1 of parentNode is changed
	so we need to go up the tree and change the min1 if needed*/
	else {
		oldMin1 = parentNode->min1;
		delete parentNode->left;
		parentNode->replaceChild(Left, Mid);
		parentNode->replaceChild(Mid, Right);
		parentNode->replaceChild(Right, Empty);
		newMin1 = parentNode->min1;
		//updating 'min1' from parent up to the root of the tree
		updateMin1FromParentToRoot(parentNode->parent->asInternal(), oldMin1, newMin1);
	}
}//deleteLeafFromParentWith3Leaves

void TwoThreeTree::resolveParentWithOneChild(InternalNode* parentNode) {
	InternalNode* grandParent = parentNode->parent->asInternal();

	//if parentNode is the root of the tree, then his parent (=grandParent) is nullptr
	if (grandParent == nullptr) {
		root = parentNode->left;
		parentNode->replaceChild(Left, Empty);
		delete parentNode;
	}

	//CASE 1: parentNode is the right child of it's parent (=grandParent)
	else if (parentNode == grandParent->right)
		resolveParentWithOneChildIsRight(parentNode, grandParent);

	//CASE 2: parentNode is the mid child of it's parent (=grandParent)
	else if (parentNode == grandParent->mid)
		resolveParentWithOneChildIsMid(parentNode, grandParent);

	//CASE 3: parentNode is the left child of it's parent (=grandParent)
	else
		resolveParentWithOneChildIsLeft(parentNode, grandParent);
	
	//if grandParent is now having 1 child, we need to make this process all over again
	if (grandParent != nullptr && grandParent->hasOneChild())
		resolveParentWithOneChild(grandParent);

}//resolveParentWithOneChild

void TwoThreeTree::resolveParentWithOneChildIsRight(InternalNode* parentNode, InternalNode* grandParent) {
	InternalNode* cousionNode;

	cousionNode = grandParent->mid->asInternal();

	//cousion has 3 children - we need to borrow his child
	if (cousionNode->hasRightChild()) {
		parentNode->replaceChild(Mid, Left);
		parentNode->left = cousionNode->right;
		parentNode->min1 = cousionNode->min3;
		parentNode->left->parent = parentNode;
		grandParent->min3 = parentNode->min1;
		cousionNode->replaceChild(Right, Empty);
	}
	//cousion has only 2 children - we need to give him our child
	else {
		cousionNode->right = parentNode->left;
		cousionNode->min3 = parentNode->min1;
		cousionNode->right->parent = cousionNode;
		parentNode->replaceChild(Left, Empty);
		delete grandParent->right;
		grandParent->replaceChild(Right, Empty);
	}
}//resolveParentWithOneChildIsRight

void TwoThreeTree::resolveParentWithOneChildIsMid(InternalNode* parentNode, InternalNode* grandParent) {
	InternalNode* cousionNode;

	//grandParent has right child - so we will negotiate with the right as cousion
	if (grandParent->hasRightChild()) {
		cousionNode = grandParent->right->asInternal();

		//cousion has 3 children - we need to borrow his child
		if (cousionNode->hasRightChild()) {
			parentNode->mid = cousionNode->left;
			parentNode->min2 = cousionNode->min1;
			parentNode->mid->parent = parentNode;
			grandParent->min3 = cousionNode->min1;
			cousionNode->replaceChild(Left, Mid);
			cousionNode->replaceChild(Mid, Right);
		}
		//cousion has only 2 children - we need to give him our child
		else {
			cousionNode->replaceChild(Right, Mid);
			cousionNode->replaceChild(Mid, Left);
			cousionNode->left = parentNode->left;
			cousionNode->min1 = parentNode->min1;
			cousionNode->left->parent = cousionNode;
			grandParent->min3 = cousionNode->min1;
			parentNode->replaceChild(Left, Empty);
			delete grandParent->mid;
			grandParent->replaceChild(Mid, Right);
		}
	}
	//grandParent doesnt have right child - so we will negotiate with the left as cousion
	else {
		cousionNode = grandParent->left->asInternal();

		//cousion has 3 children - we need to borrow his child
		if (cousionNode->hasRightChild()) {
			parentNode->replaceChild(Mid, Left);
			parentNode->left = cousionNode->right;
			parentNode->min1 = cousionNode->min3;
			parentNode->left->parent = parentNode;
			grandParent->min2 = parentNode->min1;
			cousionNode->replaceChild(Right, Empty);
		}
		//cousion has only 2 children - we need to give him our child
		else {
			cousionNode->right = parentNode->left;
			cousionNode->min3 = parentNode->min1;
			cousionNode->right->parent = cousionNode;
			parentNode->replaceChild(Left, Empty);
			delete grandParent->mid;
			grandParent->replaceChild(Mid, Empty);
		}
	}
}//resolveParentWithOneChildIsMid

void TwoThreeTree::resolveParentWithOneChildIsLeft(InternalNode* parentNode, InternalNode* grandParent) {
	InternalNode* cousionNode;

	cousionNode = grandParent->mid->asInternal();

	//cousion has 3 children - we need to borrow his child
	if (cousionNode->hasRightChild()) {
		parentNode->mid = cousionNode->left;
		parentNode->min2 = cousionNode->min1;
		parentNode->mid->parent = parentNode;
		cousionNode->replaceChild(Left, Mid);
		cousionNode->replaceChild(Mid, Right);
		grandParent->min2 = cousionNode->min1;
	}
	//cousion has only 2 children - we need to give him our child
	else {
		cousionNode->replaceChild(Right, Mid);
		cousionNode->replaceChild(Mid, Left);
		cousionNode->left = parentNode->left;
		cousionNode->min1 = parentNode->min1;
		cousionNode->left->parent = cousionNode;
		parentNode->replaceChild(Left, Empty);
		grandParent->min2 = cousionNode->min1;
		delete grandParent->left;
		grandParent->replaceChild(Left, Mid);
		grandParent->replaceChild(Mid, Right);
	}
}//resolveParentWithOneChildIsLeft



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



