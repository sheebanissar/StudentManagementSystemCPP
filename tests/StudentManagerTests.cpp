#include "StudentManager.h"

#include <gtest/gtest.h>

#include <limits>
#include <sstream>

TEST(StudentManagerTests, AddsValidStudent)
{
    StudentManager manager;

    EXPECT_TRUE(manager.addStudent(Student(1, "Ava Patel", 85.5)));

    const Student* student = manager.findStudentById(1);
    ASSERT_NE(student, nullptr);
    EXPECT_EQ(student->getName(), "Ava Patel");
    EXPECT_DOUBLE_EQ(student->getMarks(), 85.5);
}

TEST(StudentManagerTests, RejectsDuplicateStudentIdAndPreservesOriginal)
{
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(1, "Ava Patel", 85.5)));

    EXPECT_FALSE(manager.addStudent(Student(1, "Different Student", 90.0)));

    const Student* student = manager.findStudentById(1);
    ASSERT_NE(student, nullptr);
    EXPECT_EQ(student->getName(), "Ava Patel");
    EXPECT_DOUBLE_EQ(student->getMarks(), 85.5);
}

TEST(StudentManagerTests, FindsExistingStudentById)
{
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(7, "Noah Kim", 92.0)));

    const Student* student = manager.findStudentById(7);

    ASSERT_NE(student, nullptr);
    EXPECT_EQ(student->getStudentId(), 7);
    EXPECT_EQ(student->getName(), "Noah Kim");
}

TEST(StudentManagerTests, ReturnsNullptrForNonExistingStudentId)
{
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(7, "Noah Kim", 92.0)));

    EXPECT_EQ(manager.findStudentById(8), nullptr);
}

TEST(StudentManagerTests, RejectsInvalidStudentInputs)
{
    StudentManager manager;

    EXPECT_FALSE(manager.addStudent(Student(0, "Zero ID", 50.0)));
    EXPECT_FALSE(manager.addStudent(Student(-1, "Negative ID", 50.0)));
    EXPECT_FALSE(manager.addStudent(Student(2, "", 50.0)));
    EXPECT_FALSE(manager.addStudent(Student(3, "   \t", 50.0)));
    EXPECT_FALSE(manager.addStudent(Student(4, "Low marks", -0.1)));
    EXPECT_FALSE(manager.addStudent(Student(5, "High marks", 100.1)));
    EXPECT_FALSE(manager.addStudent(
        Student(6, "Infinite marks", std::numeric_limits<double>::infinity())));
    EXPECT_FALSE(manager.addStudent(
        Student(7, "NaN marks", std::numeric_limits<double>::quiet_NaN())));

    EXPECT_FALSE(manager.calculateAverageMarks().has_value());
}

TEST(StudentManagerTests, AcceptsMarksAtInclusiveBoundaries)
{
    StudentManager manager;

    EXPECT_TRUE(manager.addStudent(Student(1, "Minimum Marks", 0.0)));
    EXPECT_TRUE(manager.addStudent(Student(2, "Maximum Marks", 100.0)));
}

TEST(StudentManagerTests, HandlesEmptyStudentCollection)
{
    StudentManager manager;
    std::ostringstream output;

    manager.displayStudents(output);

    EXPECT_EQ(output.str(), "No students found.\n");
    EXPECT_FALSE(manager.calculateAverageMarks().has_value());
    EXPECT_EQ(manager.findTopStudent(), nullptr);
}

TEST(StudentManagerTests, CalculatesAverageMarks)
{
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(1, "Ava", 80.0)));
    ASSERT_TRUE(manager.addStudent(Student(2, "Noah", 100.0)));

    const std::optional<double> average = manager.calculateAverageMarks();

    ASSERT_TRUE(average.has_value());
    EXPECT_DOUBLE_EQ(*average, 90.0);
}

TEST(StudentManagerTests, FindsStudentWithHighestMarks)
{
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(1, "Ava", 80.0)));
    ASSERT_TRUE(manager.addStudent(Student(2, "Noah", 99.0)));
    ASSERT_TRUE(manager.addStudent(Student(3, "Mia", 91.0)));

    const Student* topStudent = manager.findTopStudent();

    ASSERT_NE(topStudent, nullptr);
    EXPECT_EQ(topStudent->getStudentId(), 2);
}

TEST(StudentManagerTests, DisplaysAllStudents)
{
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(1, "Ava", 80.0)));
    ASSERT_TRUE(manager.addStudent(Student(2, "Noah", 95.5)));
    std::ostringstream output;

    manager.displayStudents(output);

    EXPECT_EQ(output.str(),
              "ID: 1, Name: Ava, Marks: 80\n"
              "ID: 2, Name: Noah, Marks: 95.5\n");
}
