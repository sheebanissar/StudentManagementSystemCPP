#include "MockStudentManager.h"
#include "StudentManagementController.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

using ::testing::Return;
using ::testing::Truly;

TEST(StudentManagementControllerTests, AddsStudentAndReportsSuccess)
{
    MockStudentManager studentManager;
    std::istringstream input("1\n12\nAva Patel\n91.5\n0\n");
    std::ostringstream output;

    EXPECT_CALL(
        studentManager,
        addStudent(Truly([](const Student& student) {
            return student.getStudentId() == 12 &&
                   student.getName() == "Ava Patel" &&
                   student.getMarks() == 91.5;
        })))
        .WillOnce(Return(true));

    StudentManagementController controller(studentManager, input, output);
    controller.run();

    EXPECT_NE(output.str().find("Student added successfully."), std::string::npos);
}

TEST(StudentManagementControllerTests, ReportsWhenSearchDoesNotFindStudent)
{
    MockStudentManager studentManager;
    std::istringstream input("3\n404\n0\n");
    std::ostringstream output;

    EXPECT_CALL(studentManager, findStudentById(404))
        .WillOnce(Return(nullptr));

    StudentManagementController controller(studentManager, input, output);
    controller.run();

    EXPECT_NE(output.str().find("Student not found."), std::string::npos);
}

TEST(StudentManagementControllerTests, DisplaysFoundStudent)
{
    MockStudentManager studentManager;
    const Student foundStudent(23, "Noah Kim", 88.0);
    std::istringstream input("3\n23\n0\n");
    std::ostringstream output;

    EXPECT_CALL(studentManager, findStudentById(23))
        .WillOnce(Return(&foundStudent));

    StudentManagementController controller(studentManager, input, output);
    controller.run();

    EXPECT_NE(
        output.str().find("ID: 23, Name: Noah Kim, Marks: 88"),
        std::string::npos);
}
