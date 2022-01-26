#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>
using namespace std;

class Student{
public:
    Student();
    Student(string name, int ID);
    
    void set_Name(string name);
    void set_ID(int ID);

    const string get_Name() const;
    const int get_ID() const;

private:
    string name;
    int ID;
    

};

#endif