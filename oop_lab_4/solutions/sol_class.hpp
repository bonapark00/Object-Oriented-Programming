#ifndef __CLASS_H__
#define __CLASS_H__

#include <string>
#include "student.hpp"

using namespace std;

class Class
{
public:
	/**
	Constructors
	*/
	Class();
	Class(string className, string instructorName);

	/**
	Functions for Gang of Three Rule
	 1) Copy Constructor
	 2) Destructor
	 3) Overloaded Assignment Operator
	*/

	// copy constructor
	Class(const Class& other);
	// destructor
	~Class();
	//overloaded assign operator
	Class& operator =(const Class& other);

	/**
	Interface functions required by the specification of project 4.
	*/
	void SetClassName(string className, string instructorName);
	void Register(string studentName, int studentID);
	void Withdraw(int studentID);
	void Display() const;

	/**
	These get-functions are not required. However, I added these functions as an example.
	Other programmers can access number of students and their name and student ID using
	below get functions.

	cf) GetStudentIndex function returns index of the Student object of the studentID.
	 And it returns -1 when the studentID doesn't exist in list.
	*/
	const int		GetNumOfStudents() const;
	const int		GetStudentID(int index) const;
	const int		GetStudentIndex(int studentID) const;
	const string	GetStudentName(int index) const;

private:
	string mClassName;
	string mInstructorName;
	int mNumOfStudents; // mNumOfStudents designate the actual number of students and is less than mListCapacity.
	int mListCapacity; // mListCapacity designate the size of allocated memory of student list.
	Student* mStudentList;

	/**
	Resize function is used for resizing dynamic array of student list.
	To reduce overhead of reallocating array at every time modifying the student list,
	assign enough large array when the remain space is empty.
	On the contrary, when too many space remain empty, reduce the array size fit to 
	accommodate current size of student list.
	*/
	void Resize(int currentNum, int requiredNum, int& capacity, Student** list) const;
};


#endif /*__CLASS_H__*/
