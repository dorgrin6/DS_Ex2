
#ifndef _LEAF_NODE_H_
#define  _LEAF_NODE_H_
#include <string>
using namespace std;
#include "Node.h"

class LeafNode : public Node {
	friend TwoThreeTree;
	//private data student
	class Student {
		int id = 0;
		string name = "";
		float average = 0;
	};


	virtual bool isLeaf() const{
		return true;
	}


};

#endif
