#include "Student.h"

#include <utility>

Student::Student(int studentId, std::string name, double marks)
    : studentId_(studentId), name_(std::move(name)), marks_(marks)
{
}

int Student::getStudentId() const
{
    return studentId_;
}

const std::string& Student::getName() const
{
    return name_;
}

double Student::getMarks() const
{
    return marks_;
}
