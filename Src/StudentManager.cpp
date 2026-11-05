#include "StudentManager.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <ostream>

bool StudentManager::addStudent(const Student& student)
{
    const bool hasName = std::any_of(
        student.getName().begin(),
        student.getName().end(),
        [](unsigned char character) { return !std::isspace(character); });

    if (student.getStudentId() <= 0 ||
        !hasName ||
        !std::isfinite(student.getMarks()) ||
        student.getMarks() < 0.0 ||
        student.getMarks() > 100.0 ||
        findStudentById(student.getStudentId()) != nullptr)
    {
        return false;
    }

    students_.push_back(student);
    return true;
}

void StudentManager::displayStudents(std::ostream& output) const
{
    if (students_.empty())
    {
        output << "No students found.\n";
        return;
    }

    for (const Student& student : students_)
    {
        output << "ID: " << student.getStudentId()
               << ", Name: " << student.getName()
               << ", Marks: " << student.getMarks() << '\n';
    }
}

const Student* StudentManager::findStudentById(int studentId) const
{
    const auto student = std::find_if(
        students_.begin(),
        students_.end(),
        [studentId](const Student& current) {
            return current.getStudentId() == studentId;
        });

    return student == students_.end() ? nullptr : &*student;
}

std::optional<double> StudentManager::calculateAverageMarks() const
{
    if (students_.empty())
    {
        return std::nullopt;
    }

    double totalMarks = 0.0;
    for (const Student& student : students_)
    {
        totalMarks += student.getMarks();
    }

    return totalMarks / static_cast<double>(students_.size());
}

const Student* StudentManager::findTopStudent() const
{
    if (students_.empty())
    {
        return nullptr;
    }

    const auto topStudent = std::max_element(
        students_.begin(),
        students_.end(),
        [](const Student& left, const Student& right) {
            return left.getMarks() < right.getMarks();
        });

    return &*topStudent;
}
