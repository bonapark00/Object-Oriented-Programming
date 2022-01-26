#ifndef __CLASS_H__
#define __CLASS_H__

#include <string>
#include "my_student.hpp"
using namespace std;

class Class{
public:

    // constructor
    Class();
    Class(string class_name, string prof_name);

    // copy constructor
    Class(Class& original);

    // '=' operator
    Class& operator =(const Class& right);

    // other functions
    void SetClassName(string class_name, string prof_name);
    void Register(string name, int ID);
    void Withdraw(int ID);
    void Display() const;   // const 꼭 필요한가?

    // destructor
    ~Class();
private:
    string class_name;
    string prof_name;
    int totalStudentNum;
    int lstCapacity;
    Student* lst_students;














};

#endif 