#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#include <string>
#include <iostream>
using namespace std;
class StudentException{
protected:
	int id;
	float average;
	string name;

public:
	StudentException(int _id, const string &_name, float _average):
	id(_id),name(_name),average(_average){}
	virtual void print() const = 0;
};

class InvalidIdException : public StudentException
{
public:
	InvalidIdException(int _id, const string &_name, float _average) : StudentException(id,name,average) {}
	virtual void print() const
	{
		cout << "The id " << id << " is not valid for " << name << endl;
	}
};

class InvalidNameException : public StudentException
{
public:
	InvalidNameException(int _id, const string &_name, float _average) : StudentException(id, name, average) {}
	virtual void print() const
	{
		cout << "An empty name is not valid for the person with the id " << id << endl;
	}
};

class InvalidAvgException : public StudentException
{
public:
	InvalidAvgException(int _id, const string &_name, float _average) : StudentException(id, name, average) {}
	virtual void print() const
	{
		cout << "Average can't be negative for person with id " << id << endl;
	}
};

class KeyAlreadyExists{
public:
	void print() const
	{
		cout << "Key already exists\n";
	}
};



#endif
