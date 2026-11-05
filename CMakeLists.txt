cmake_minimum_required(VERSION 3.20)

project(StudentManagementSystem
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(StudentApp
    Src/main.cpp
    Src/Student.cpp
    Src/StudentManager.cpp
    Src/StudentManagementController.cpp
)

target_include_directories(StudentApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

include(CTest)

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(StudentTests
        tests/StudentTests.cpp
        tests/StudentManagerTests.cpp
        tests/StudentManagementControllerTests.cpp
        tests/StudentManagementControllerMockTests.cpp
        Src/Student.cpp
        Src/StudentManager.cpp
        Src/StudentManagementController.cpp
    )

    target_include_directories(StudentTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
    )

    target_link_libraries(StudentTests PRIVATE
        GTest::gmock_main
    )

    include(GoogleTest)
    gtest_discover_tests(StudentTests)
endif()
