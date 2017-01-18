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

	cin >> n; // insert number of elements
	if (n < 0){
		cout << "Amount of numbers can't be negatvie\n";
		return 1;
	}


	
	for (int i=0; i<n; i++){
		cin >> ID >> name >> average;
		try{
			DataType stud(ID, name, average);
			t.insertNode(ID, &stud);
		}
		catch(StudentException &e){
			e.print();
			return 1;
		}
		catch (KeyAlreadyExists &e){
			e.print();
			return 1;
		}
	}
	
	cin >> x;//get number to delete
	
	if (x < 0){
		cout << "Illegal number, no negative numbers in tree\n";
		return 1;
	}

	//find x, delete it if exists
	if (t.deleteNode(x) == false){
		cout << "Key does not exist\n"; //key wasn't found
	}

	t.print();//print tree leaves
}