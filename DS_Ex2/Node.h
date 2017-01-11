#ifndef _NODE_H_
#define _NODE_H_


class TwoThreeTree;

class Node {
	int key;
	Node *parent;
	
public:
	friend TwoThreeTree;
	Node(int _key=0,Node* _parent=nullptr):key(_key),parent(_parent){}

	virtual bool isLeaf()= 0;


};

#endif



