// include꼭 바꾸기!!
#include "my_student.hpp"

// constructors
Student::Student()
{
    name = "";
    ID = 0;
}

Student::Student(string name, int ID)
{
    this->name = name;
    this->ID = ID;
}

// setting functions
void Student::set_Name(string name)
{
    this->name = name;
}

void Student::set_ID(int ID)
{
    this->ID = ID;
}

const string Student::get_Name() const
{
    return name;
}

const int Student::get_ID() const
{
    return ID;
}


