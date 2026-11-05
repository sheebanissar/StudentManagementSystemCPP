#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student
{
public:
    Student(int studentId, std::string name, double marks);

    int getStudentId() const;
    const std::string& getName() const;
    double getMarks() const;

private:
    int studentId_;
    std::string name_;
    double marks_;
};

#endif
