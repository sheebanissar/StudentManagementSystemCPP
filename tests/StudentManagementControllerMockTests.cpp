#include "MockStudentManager.h"
#include "StudentManagementController.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;
using ::testing::Truly;

TEST(StudentManagementControllerMockTests, ReportsSuccessfulAdd)
{
    StrictMock<MockStudentManager> studentManager;
    std::istringstream input("1\n12\nAva Patel\n91.5\n0\n");
    std::ostringstream output;

    EXPECT_CALL(
        studentManager,
        addStudent(Truly([](const Student& student) {
            return student.getStudentId() == 12 &&
                   student.getName() == "Ava Patel" &&
                   student.getMarks() == 91.5;
        })))
        .Times(1)
        .WillOnce(Return(true));

    StudentManagementController controller(studentManager, input, output);
    controller.run();

    EXPECT_NE(output.str().find("Student added successfully."), std::string::npos);
}

TEST(StudentManagementControllerMockTests, ReportsDependencyFailureWhenAddIsRejected)
{
    StrictMock<MockStudentManager> studentManager;
    std::istringstream input("1\n12\nAva Patel\n91.5\n0\n");
    std::ostringstream output;

    EXPECT_CALL(studentManager, addStudent(_))
        .Times(1)
        .WillOnce(Return(false));

    StudentManagementController controller(studentManager, input, output);
    controller.run();

    EXPECT_NE(
        output.str().find("Could not add student. The ID may already exist."),
        std::string::npos);
    EXPECT_EQ(output.str().find("Student added successfully."), std::string::npos);
}

TEST(StudentManagementControllerMockTests, ReportsDuplicateStudentRejection)
{
    StrictMock<MockStudentManager> studentManager;
    std::istringstream input(
        "1\n12\nAva Patel\n91.5\n"
        "1\n12\nAva Patel\n91.5\n"
        "0\n");
    std::ostringstream output;

    EXPECT_CALL(studentManager, addStudent(_))
        .Times(2)
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    StudentManagementController controller(studentManager, input, output);
    controller.run();

    const std::string text = output.str();
    EXPECT_NE(text.find("Student added successfully."), std::string::npos);
    EXPECT_NE(
        text.find("Could not add student. The ID may already exist."),
        std::string::npos);
}

TEST(StudentManagementControllerMockTests, DoesNotCallManagerForInvalidStudentId)
{
    StrictMock<MockStudentManager> studentManager;
    std::istringstream input("1\n0\n");
    std::ostringstream output;

    StudentManagementController controller(studentManager, input, output);
    controller.run();

    EXPECT_NE(
        output.str().find("Student ID must be a positive number."),
        std::string::npos);
}

TEST(StudentManagementControllerMockTests, CallsSearchDependencyOncePerSearch)
{
    StrictMock<MockStudentManager> studentManager;
    const Student foundStudent(23, "Noah Kim", 88.0);
    std::istringstream input("3\n23\n3\n404\n0\n");
    std::ostringstream output;

    EXPECT_CALL(studentManager, findStudentById(23))
        .Times(1)
        .WillOnce(Return(&foundStudent));
    EXPECT_CALL(studentManager, findStudentById(404))
        .Times(1)
        .WillOnce(Return(nullptr));

    StudentManagementController controller(studentManager, input, output);
    controller.run();

    EXPECT_NE(
        output.str().find("ID: 23, Name: Noah Kim, Marks: 88"),
        std::string::npos);
    EXPECT_NE(output.str().find("Student not found."), std::string::npos);
}
