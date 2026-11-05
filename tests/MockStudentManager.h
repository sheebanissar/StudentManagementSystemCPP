#ifndef MOCK_STUDENT_MANAGER_H
#define MOCK_STUDENT_MANAGER_H

#include "IStudentManager.h"

#include <gmock/gmock.h>

class MockStudentManager : public IStudentManager
{
public:
    MOCK_METHOD(bool, addStudent, (const Student& student), (override));
    MOCK_METHOD(void, displayStudents, (std::ostream& output), (const, override));
    MOCK_METHOD(const Student*, findStudentById, (int studentId), (const, override));
    MOCK_METHOD(
        std::optional<double>,
        calculateAverageMarks,
        (),
        (const, override));
    MOCK_METHOD(const Student*, findTopStudent, (), (const, override));
};

#endif
