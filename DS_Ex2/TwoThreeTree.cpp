#include "TwoThreeTree.h"
#include <iostream>
#include "InternalNode.h"





bool TwoThreeTree::insertNode(Node * toInsert){
	bool res;
	LeafNode *parentNode = findNodeRec(root, toInsert->key);

	if (parentNode == nullptr){
		return false;
	}
	//case 1
	if (parentNode->)


}

LeafNode* TwoThreeTree::findNode(int key){
	InternalNode* root = (InternalNode *)this->root;
	LeafNode *res;
	res = findNodeRec(root, key);
	
	if (res->key != key){
		cout << "Key not found" << endl;
		return nullptr;
	}

	return res;	
}
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
			findNodeRec(inRoot->right, key);
		}
		else if (key>=inRoot->min2){
			findNodeRec(inRoot->mid, key);
		}
		else{
			findNodeRec(inRoot->left, key);
		}
	}
}


void TwoThreeTree::print(){
	list<LeafNode::Student>::const_iterator iter;

	for (iter= leaves.begin();iter != leaves.end();++iter){
		//print student
	}
}
