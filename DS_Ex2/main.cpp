#include "TwoThreeTree.h"
#include "Student.h"


int main(){
	Student rami(10, "rami", 70);
	Student moshe(50, "moshe", 80);
	Student dani(100, "dani", 90);
	Student idan(200, "Idan", 100);
	Student yuval(250, "yuval", 90);
	Student yossi(275, "yossi", 95);
	Student dor(300, "dor", 100);
	Student roni(350, "roni", 65);
	Student gadi(400, "gadi", 60);
	Student frank(500, "frank", 85);
	Student gili(600, "gili", 70);
	Student jay(300, "jay", 60); //fake student
	
	
	TwoThreeTree t;


	t.insertNode(idan.getID(), &idan);
	t.insertNode(dor.getID(), &dor);
	t.insertNode(dani.getID(), &dani);
	t.insertNode(moshe.getID(), &moshe);
	t.insertNode(gadi.getID(), &gadi);
	t.insertNode(frank.getID(), &frank);
	t.insertNode(yuval.getID(), &yuval);
	t.insertNode(yossi.getID(), &yossi);
	t.insertNode(rami.getID(), &rami);
	t.insertNode(jay.getID(), &jay); //this suppose to print fail message
	t.insertNode(gili.getID(), &gili);
	t.insertNode(roni.getID(), &roni);


	t.deleteNode(400);
	t.deleteNode(300);
	t.deleteNode(10);
	t.deleteNode(50);
	t.print();




	getchar();
}