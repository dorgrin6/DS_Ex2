#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <ostream>
#include <string>
#include "Exceptions.h"
using namespace std;

class Student {
	int id;
	string name;
	float average;

public:
	//CTOR
	Student(int _id = 0, string _name = "", float _avg=0){
		if (_id < 0)
			throw InvalidIdException(_id, _name, _avg);
		if (_name.compare("") == 0)
			throw InvalidNameException(_id, _name, _avg);
		if (_avg < 0)
			throw InvalidAvgException(_id, _name, _avg);


		id = _id;
		name = _name; // string copy
		average = _avg;
	}

	//getID: return the id of student
	int getID() const { return id; }

	friend ostream& operator<< (ostream& os, const Student& student) {
		os << student.id << " "<<student.name<<" "<<student.average << endl;
		return os;
	}


	~Student(){}
};

#endif