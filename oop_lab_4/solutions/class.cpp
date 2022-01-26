#include "class.hpp"
#include <iostream>

Class::Class()
{
	mNumOfStudents = 0;
	mListCapacity = 0;

	
	mStudentList = NULL;
}

Class::Class(string className, string instructorName)
{
	mClassName = className;
	mInstructorName = instructorName;
	mNumOfStudents = 0;
	mListCapacity = 0;
	mStudentList = NULL;
}

Class::Class(const Class& other)
{
	// This copy constructor use assignment operator to not write same code again(in other words, for re-use code).
	// However, be careful that we have to initialize member variables before calling assignment operator.
	// If don't do that, it can cause deallocation of wrong address which is not allocated before and 
	// program stopped by runtime error, because mStudentList can have trash address value.
	mNumOfStudents = 0;
	mListCapacity = 0;
	mStudentList = NULL;

	*this = other;
}

Class& Class::operator =(const Class& other)
{
	if (this == &other) // Don't need to proceed when assignment itself to itself.
		return *this;

	mClassName = other.mClassName;
	mInstructorName = other.mInstructorName;
	Resize(mNumOfStudents, other.mNumOfStudents, mListCapacity, &mStudentList);

	// Copy students
	for (int i = 0; i < other.mNumOfStudents; i++)
		mStudentList[i] = other.mStudentList[i];
	
	mNumOfStudents = other.mNumOfStudents;
	return *this;
}

Class::~Class()
{
	if (mStudentList != NULL)
		delete[] mStudentList;
}






void Class::SetClassName(string className, string instructorName)
{
	mClassName = className;
	mInstructorName = instructorName;
}

void Class::Register(string studentName, int studentID)
{
	Resize(mNumOfStudents, mNumOfStudents + 1, mListCapacity, &mStudentList);

	mStudentList[mNumOfStudents].SetName(studentName);
	mStudentList[mNumOfStudents].SetID(studentID);
	mNumOfStudents++;
}

void Class::Withdraw(int studentID)
{
	int index = GetStudentIndex(studentID);

	// Terminate function when the student doesn't exist in the list
	if (index == -1)
		return;

	// Erase withdrawl student by moving all students after withdrawl students from current position to one position forward.
	for (int i = index; i < mNumOfStudents - 1; i++)
		mStudentList[i] = mStudentList[i + 1];

	// Call Resize function and then reduce the number of students.
	Resize(mNumOfStudents, mNumOfStudents-1, mListCapacity, &mStudentList);
	mNumOfStudents--;
}

void Class::Display() const
{
	cout << "Prof. :" << mInstructorName << "\t\tClass Name :" << mClassName << endl
		<< "-------------------------------------------------------------------" << endl
		<< "Total number of students : " << mNumOfStudents <<endl
		<< "List Capacity :"<<mListCapacity<< endl << endl;

	for (int i = 0; i < mNumOfStudents; i++)
	{
		cout << mStudentList[i].GetName() << "\t\t" << mStudentList[i].GetID() << endl;
	}

	cout << endl << endl << endl;
}

const int Class::GetNumOfStudents() const
{
	return mNumOfStudents;
}

const int Class::GetStudentID(int index) const
{
	return mStudentList[index].GetID();
}

const int Class::GetStudentIndex(int studentID) const
{
	int index = -1;

	// Search the student with studentID
	for (int i = 0; i < mNumOfStudents; i++)
	{
		if (mStudentList[i].GetID() == studentID)
		{
			index = i;
			break;
		}
	}

	return index;
}

const string Class::GetStudentName(int index) const
{
	return mStudentList[index].GetName();
}





void Class::Resize(const int currentNum, const int requiredNum, int& capacity, Student** list) const
{
	int prevCapacity = capacity;

	if (requiredNum > 0)
	{
		// Initialize capacity as 2 when it is zero.
		if (capacity == 0)
			capacity = 1;

		// When capacity is too small, double capacity size until it is enough large to accommodate required students.
		while (capacity < requiredNum)
			capacity *= 2;

		// If capacity is too big, reduce capacity size suitable to required size.
		// On the other hand, the condition of while statement prevent the capacity size from being reduced too tightly.
		while (capacity >= requiredNum * 2)
			capacity /= 2;
	}
	else if (capacity > 0) // If required number is zero and capacity is too large, reduce capacity to initial value.
	{
		capacity = 0;
	}

	// If capacity size is changed, reallocate array and copy all students from the previous array
	if (prevCapacity != capacity)
	{
		Student* tempList = *list;
		*list = new Student[capacity];

		int copyCnt = (currentNum < capacity) ? currentNum : capacity;
		for (int i = 0; i < copyCnt; i++)
			(*list)[i] = tempList[i];

		// Do not forget delete unused array
		if (tempList != NULL)
			delete[] tempList;
	}
}
