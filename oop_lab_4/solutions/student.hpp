#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>
using namespace std;

//class about the information of students
class Student
{
public:
	/**
	Constructors
	*/
	Student();
	Student(int ID, string name);
	Student(const Student& other);

	/**
	Set functions
	*/
	void SetID(int ID);
	void SetName(string name);
	
	/**
	Get functions
	*/
	const int		GetID() const;
	const string	GetName() const;

	/**
	Overloaded operators being utilized in Class class.
	For example, operator == and != can be used to find student with ID which is passed to Withdraw function.
	*/
	Student& operator =(const Student& other);
	bool operator ==(const Student& other) const;
	bool operator !=(const Student& other) const;

private:
	int mID;
	string mName;
};

#endif /*__STUDENT_H__*/
