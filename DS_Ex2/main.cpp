/*
 *TWOTHREETREE: implementation of 2-3 Tree as presented in class.
 *Insturctions:
 */
#include "TwoThreeTree.h"
#include "Student.h"
#include <string>

int main(){
	int ID;
	string name;
	float average;
	int x; // number inserted
	TwoThreeTree t; // tree

	int n; // num of elments in tree
	cin >> n;
	
	for (int i=0; i<n; i++){
		cin >> ID >> name >> average;
		DataType stud(ID, name, average);
		t.insertNode(ID, &stud);
	}

	cin >> x;
	//find x, delete it if exists
	if (t.deleteNode(x)){
		t.print();
	}
}