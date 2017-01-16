/*
 *	TwoThreeTree: implementation of 2-3 Tree as presented in class.
 *	Insturctions: insert the amount of numbers to input, then at the following order of each student: 
 *		ID, name, average.
 *	Lastly, enter the ID of a student to delete.
 *	
 *	 Presenters: Idan Gur and Dor Grinshpan 
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
	t.deleteNode(x);
	t.print();
}