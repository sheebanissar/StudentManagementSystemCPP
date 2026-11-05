#include "StudentManagementController.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace
{
bool readInteger(
    std::istream& input,
    std::ostream& output,
    const std::string& prompt,
    int& value)
{
    while (true)
    {
        output << prompt;
        std::string line;
        if (!std::getline(input, line))
        {
            return false;
        }

        std::istringstream lineInput(line);
        int parsedValue = 0;
        if ((lineInput >> parsedValue) && (lineInput >> std::ws).eof())
        {
            value = parsedValue;
            return true;
        }

        output << "Please enter a valid whole number.\n";
    }
}

bool readMarks(
    std::istream& input,
    std::ostream& output,
    double& marks)
{
    while (true)
    {
        output << "Enter marks (0-100): ";
        std::string line;
        if (!std::getline(input, line))
        {
            return false;
        }

        std::istringstream lineInput(line);
        double parsedMarks = 0.0;
        if ((lineInput >> parsedMarks) &&
            (lineInput >> std::ws).eof() &&
            std::isfinite(parsedMarks) &&
            parsedMarks >= 0.0 &&
            parsedMarks <= 100.0)
        {
            marks = parsedMarks;
            return true;
        }

        output << "Please enter a number from 0 to 100.\n";
    }
}

bool readName(
    std::istream& input,
    std::ostream& output,
    std::string& name)
{
    while (true)
    {
        output << "Enter student name: ";
        if (!std::getline(input, name))
        {
            return false;
        }

        const auto firstCharacter = std::find_if_not(
            name.begin(),
            name.end(),
            [](unsigned char character) { return std::isspace(character); });
        const auto lastCharacter = std::find_if_not(
            name.rbegin(),
            name.rend(),
            [](unsigned char character) { return std::isspace(character); })
                                        .base();

        if (firstCharacter != name.end())
        {
            name = std::string(firstCharacter, lastCharacter);
            return true;
        }

        output << "Student name cannot be empty.\n";
    }
}

bool readPositiveId(
    std::istream& input,
    std::ostream& output,
    int& studentId)
{
    while (true)
    {
        if (!readInteger(input, output, "Enter student ID: ", studentId))
        {
            return false;
        }
        if (studentId > 0)
        {
            return true;
        }
        output << "Student ID must be a positive number.\n";
    }
}

void printStudent(std::ostream& output, const Student& student)
{
    output << "ID: " << student.getStudentId()
           << ", Name: " << student.getName()
           << ", Marks: " << student.getMarks() << '\n';
}

void printMenu(std::ostream& output)
{
    output << "\nStudent Management System\n"
           << "1. Add student\n"
           << "2. Display all students\n"
           << "3. Find student by ID\n"
           << "4. Calculate average marks\n"
           << "5. Find top student\n"
           << "0. Exit\n";
}
} // namespace

StudentManagementController::StudentManagementController(
    IStudentManager& studentManager,
    std::istream& input,
    std::ostream& output)
    : studentManager_(studentManager), input_(input), output_(output)
{
}

void StudentManagementController::run()
{
    int choice = 0;

    while (true)
    {
        printMenu(output_);
        if (!readInteger(input_, output_, "Choose an option: ", choice))
        {
            output_ << "\nInput ended. Exiting.\n";
            return;
        }

        switch (choice)
        {
        case 1:
        {
            int studentId = 0;
            std::string name;
            double marks = 0.0;
            if (!readPositiveId(input_, output_, studentId) ||
                !readName(input_, output_, name) ||
                !readMarks(input_, output_, marks))
            {
                output_ << "\nInput ended. Exiting.\n";
                return;
            }

            if (studentManager_.addStudent(
                    Student(studentId, std::move(name), marks)))
            {
                output_ << "Student added successfully.\n";
            }
            else
            {
                output_ << "Could not add student. The ID may already exist.\n";
            }
            break;
        }
        case 2:
            studentManager_.displayStudents(output_);
            break;
        case 3:
        {
            int studentId = 0;
            if (!readPositiveId(input_, output_, studentId))
            {
                output_ << "\nInput ended. Exiting.\n";
                return;
            }

            const Student* student =
                studentManager_.findStudentById(studentId);
            if (student == nullptr)
            {
                output_ << "Student not found.\n";
            }
            else
            {
                printStudent(output_, *student);
            }
            break;
        }
        case 4:
        {
            const std::optional<double> average =
                studentManager_.calculateAverageMarks();
            if (average.has_value())
            {
                output_ << "Average marks: " << *average << '\n';
            }
            else
            {
                output_ << "No students available to calculate an average.\n";
            }
            break;
        }
        case 5:
        {
            const Student* topStudent = studentManager_.findTopStudent();
            if (topStudent == nullptr)
            {
                output_ << "No students available.\n";
            }
            else
            {
                output_ << "Top student: ";
                printStudent(output_, *topStudent);
            }
            break;
        }
        case 0:
            output_ << "Goodbye.\n";
            return;
        default:
            output_ << "Invalid option. Please choose a listed option.\n";
            break;
        }
    }
}
