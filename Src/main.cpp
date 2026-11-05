#include "StudentManagementController.h"
#include "StudentManager.h"

#include <iostream>

int main()
{
    StudentManager studentManager;
    StudentManagementController controller(studentManager, std::cin, std::cout);
    controller.run();
    return 0;
}
