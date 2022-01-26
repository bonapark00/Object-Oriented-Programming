#include "student.hpp"

Student::Student() : mID(0), mName("")
{}

Student::Student(int ID, string name) : mID(ID), mName(name)
{}

Student::Student(const Student& other) : mID(other.mID), mName(other.mName)
{}

void Student::SetID(int ID)
{
	mID = ID;
}

void Student::SetName(string name)
{
	mName = name;
}

const int Student::GetID() const
{
	return mID;
}

const string Student::GetName() const
{
	return mName;
}

Student& Student::operator =(const Student& other)
{
	if (this == &other)
		return *this;

	mName = other.mName;
	mID = other.mID;

	return *this;
}

bool Student::operator ==(const Student& other) const
{
	return (mID == other.mID) ? true : false;
}

bool Student::operator !=(const Student& other) const
{
	return (mID != other.mID) ? true : false;
}
