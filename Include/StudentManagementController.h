#ifndef STUDENT_MANAGEMENT_CONTROLLER_H
#define STUDENT_MANAGEMENT_CONTROLLER_H

#include "IStudentManager.h"

#include <iosfwd>

class StudentManagementController
{
public:
    StudentManagementController(
        IStudentManager& studentManager,
        std::istream& input,
        std::ostream& output);

    void run();

private:
    IStudentManager& studentManager_;
    std::istream& input_;
    std::ostream& output_;
};

#endif
