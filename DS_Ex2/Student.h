#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <ostream>
#include <string>
using namespace std;

class Student {
	int id;
	string name;
	float average;

public:
	//CTOR
	Student(int _id = 0, string _name = "", float _avg=0) :id(_id), name(_name), average(_avg) {}

	//getID: return the id of student
	int getID() const { return id; }

	friend ostream& operator<< (ostream& os, const Student& student) {
		os << student.id << " "<<student.name<<" "<<student.average << endl;
		return os;
	}


	~Student(){}
};

#endif