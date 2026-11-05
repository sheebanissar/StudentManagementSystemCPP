#include "Student.h"

#include <gtest/gtest.h>

#include <limits>
#include <string>

TEST(StudentTests, ConstructorStoresProvidedValues)
{
    const Student student(42, "Ava Patel", 87.5);

    EXPECT_EQ(student.getStudentId(), 42);
    ASSERT_EQ(student.getName(), "Ava Patel");
    EXPECT_DOUBLE_EQ(student.getMarks(), 87.5);
}

TEST(StudentTests, GettersReturnValuesForNegativeInputs)
{
    // Student currently stores values without validating them.
    const Student student(-7, "", -12.5);

    EXPECT_EQ(student.getStudentId(), -7);
    EXPECT_TRUE(student.getName().empty());
    EXPECT_DOUBLE_EQ(student.getMarks(), -12.5);
}

TEST(StudentTests, GettersReturnBoundaryValues)
{
    const Student minimumStudent(
        std::numeric_limits<int>::min(), "A", 0.0);
    const Student maximumStudent(
        std::numeric_limits<int>::max(), "Z", 100.0);

    EXPECT_EQ(minimumStudent.getStudentId(), std::numeric_limits<int>::min());
    EXPECT_FALSE(minimumStudent.getName().empty());
    EXPECT_DOUBLE_EQ(minimumStudent.getMarks(), 0.0);

    EXPECT_EQ(maximumStudent.getStudentId(), std::numeric_limits<int>::max());
    ASSERT_EQ(maximumStudent.getName(), "Z");
    EXPECT_DOUBLE_EQ(maximumStudent.getMarks(), 100.0);
}
