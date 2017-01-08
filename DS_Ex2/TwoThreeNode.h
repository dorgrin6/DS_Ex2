#ifndef TWOTHREENODE
#define TWOTHREENODE

#include <string>

class TwoThreeTree;
using namespace std;

class TwoThreeNode {
	friend TwoThreeTree;
	//private data student
	class Student {
		int id = 0;
		string name = "";
		float average = 0;
	};

	int key;
	Student *data;

	TwoThreeNode *left, *mid, *right;
	int min1, min2, min3;
	TwoThreeNode *parent;
	


public:

	TwoThreeNode():key(0),data(nullptr),left(nullptr), mid(nullptr) , right(nullptr), parent(nullptr),min1(0), min2(0), min3(0)
	{}


};

#endif



