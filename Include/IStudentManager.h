#ifndef I_STUDENT_MANAGER_H
#define I_STUDENT_MANAGER_H

#include "Student.h"

#include <iosfwd>
#include <optional>

class IStudentManager
{
public:
    virtual ~IStudentManager() = default;

    virtual bool addStudent(const Student& student) = 0;
    virtual void displayStudents(std::ostream& output) const = 0;
    virtual const Student* findStudentById(int studentId) const = 0;
    virtual std::optional<double> calculateAverageMarks() const = 0;
    virtual const Student* findTopStudent() const = 0;
};

#endif
