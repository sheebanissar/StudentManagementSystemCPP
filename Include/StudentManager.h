#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "IStudentManager.h"

#include <vector>

class StudentManager : public IStudentManager
{
public:
    bool addStudent(const Student& student) override;
    void displayStudents(std::ostream& output) const override;
    const Student* findStudentById(int studentId) const override;
    std::optional<double> calculateAverageMarks() const override;
    const Student* findTopStudent() const override;

private:
    std::vector<Student> students_;
};

#endif
