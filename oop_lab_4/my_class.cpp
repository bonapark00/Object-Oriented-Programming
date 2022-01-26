#include "my_class.hpp"
#include <iostream>

Class::Class()
{
    class_name = "";
    prof_name = "";
    totalStudentNum = 0;
    lstCapacity = 0;
    lst_students = NULL;

}

Class::Class(string class_name, string prof_name)
{
    this-> class_name = class_name;
    this-> prof_name = prof_name;
    totalStudentNum = 0;
    lstCapacity = 0;
    lst_students = NULL;
}

// copy constructor
Class::Class(Class& original)
{
    // initialize member variables first
    class_name = "";
    prof_name = "";
    totalStudentNum = 0;
    lstCapacity = 0;
    lst_students = NULL;
    
    // assign original address to this object
    *this = original;
}

Class& Class::operator=(const Class& right)
{
    if(this == &right){
        return *this;
    }

    else{
    class_name = right.class_name;
    prof_name = right.prof_name;
    totalStudentNum = right.totalStudentNum;
    lstCapacity = right.lstCapacity;
    }

    // copy the student list. 
    if(lst_students != NULL){
        delete[] lst_students;       
    }
    
    lst_students = new Student[lstCapacity];

    for(int i=0; i<totalStudentNum; i++){
        lst_students[i] = right.lst_students[i];
    }
    
    return *this;
}

void Class::SetClassName(string class_name, string prof_name)
{
    this->class_name = class_name;
    this->prof_name = prof_name;
}




void Class::Register(string name, int ID){
    totalStudentNum++;
    
    // if total student number is larger than the capacity after registration,
    // we need to mutate students array and the capacity to fully accommodate all students
    if(totalStudentNum > lstCapacity){
        // increase the list capacity
        
        // the first case: only one student to register with zero totalStudentNum
        if(lstCapacity == 0){
            lstCapacity = 1;
        }    
        else{
            lstCapacity *= 2;
        }     

        // we need to increase the size of lst_student array.
        Student* lst_temp = lst_students;
        lst_students = new Student[lstCapacity];

        for(int i=0; i < totalStudentNum - 1; i++){
            lst_students[i] = lst_temp[i];
        }

    if(lst_temp != NULL){
        delete[] lst_temp;  // delete temporary list
    }
        
    }
    
    // do register new student to the lst_students 
    lst_students[totalStudentNum].set_Name(name);
    lst_students[totalStudentNum].set_ID(ID);


}

void Class::Withdraw(int ID){
    
    // we need to find the withdrawing student's index on list
    int targetIndex;
    for(int i=0; i<totalStudentNum; i++){
        if(ID == lst_students[i].get_ID()){
            targetIndex = i;
            break;
        }
    }

    if(targetIndex != (totalStudentNum - 1)){
    // do erase the target student from the lst_students
    for(int i=targetIndex; i<totalStudentNum -1; i++){
        lst_students[i] = lst_students[i+1];
    }
    }

    // the total student number decreases
    totalStudentNum--;

    // mutate the lst_students array size and lstCapacity, if necessary
    if(totalStudentNum == 0){
        lstCapacity = 0;
        delete[] lst_students;
    }

   if(totalStudentNum <= lstCapacity / 2){
        // increase the list capacity
        lstCapacity /= 2;

        // we need to decrease the size of lst_student array.   
        Student* lst_temp = lst_students;
        lst_students = new Student[lstCapacity];

        for(int i=0; i < totalStudentNum; i++){
            lst_students[i] = lst_temp[i];
        }
       
        delete[] lst_temp;  // delete temporary list
    }
}

void Class::Display() const
{
    
	cout << "Prof. :" << prof_name << "\t\tClass Name :" << class_name << "\n"
		<< "-------------------------------------------------------------------" << "\n"
		<< "Total number of students : " << totalStudentNum <<"\n"
		<< "List Capacity :"<< lstCapacity << "\n\n";

	for (int i = 0; i < totalStudentNum; i++)
	{
		cout << lst_students[i].get_Name() << "\t\t" << lst_students[i].get_ID() << "\n";
	}

	cout << "\n\n\n";
}


// destructor
Class::~Class()
{
    if(lst_students != NULL){
        delete[] lst_students;
    }
}

