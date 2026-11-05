# Student Management System Debugging Checklist

Use these questions to investigate a problem before changing code, then verify the fix.

## Understanding Existing Code

- [ ] What behavior is expected, and what happens instead?
- [ ] Can I reproduce the issue reliably? What exact inputs and steps trigger it?
- [ ] Which files, classes, functions, and data are involved in this behavior?
- [ ] How does data flow from user input through the application to its output or storage?
- [ ] Is there existing documentation, a test, or a code pattern that clarifies the intended behavior?
- [ ] What is the smallest area of code that could explain the issue?

## Compiler and Linker Errors

- [ ] What is the first diagnostic, and does it point to the original problem rather than a follow-on error?
- [ ] Does the message identify a syntax, type, declaration, or missing-include problem?
- [ ] Are declarations and definitions consistent, including names, parameter types, and namespaces?
- [ ] Are all required source files included in the build?
- [ ] Are compiler standard, include paths, and linker settings appropriate for this project?
- [ ] Did a recent change introduce the error, or does it occur in the unchanged baseline too?

## Runtime Crashes

- [ ] What exact action or input causes the crash, and can it be reproduced?
- [ ] Where does execution fail, based on a debugger, stack trace, or diagnostic output?
- [ ] Is a pointer, reference, or iterator null, invalid, or no longer pointing to a live object?
- [ ] Could an index or input value be outside its valid range?
- [ ] Does the crash depend on object lifetime, input order, or application state?
- [ ] What is the earliest point where program state becomes incorrect?

## Undefined Behavior

- [ ] Are variables initialized before they are read?
- [ ] Can an array, string, vector, or other container be accessed outside its valid bounds?
- [ ] Are pointers and references used only while their objects are alive?
- [ ] Could signed integer arithmetic overflow, or could a conversion lose or misinterpret data?
- [ ] Are iterators invalidated by a container operation and then used afterward?
- [ ] Is shared state accessed concurrently without appropriate synchronization?
- [ ] Does the issue change with compiler options, build mode, or repeated runs?

## Memory Leaks and Dangling Pointers

- [ ] Does every dynamically managed resource have a clear owner and lifetime?
- [ ] Can standard containers, automatic objects, or smart pointers manage the resource instead?
- [ ] If raw ownership is necessary, is the resource released on every normal and exceptional exit path?
- [ ] Can a pointer or reference outlive the object it refers to?
- [ ] Is a pointer retained after its object has been deleted or otherwise destroyed?
- [ ] Could `std::unique_ptr` or `std::shared_ptr` express the intended ownership more safely?

## Multi-File Dependency Problems

- [ ] Does each source file include the header that declares the symbols it uses?
- [ ] Do header declarations match the corresponding source-file definitions?
- [ ] Are include guards or `#pragma once` preventing repeated header inclusion?
- [ ] Are required source files included in the build command or project configuration?
- [ ] Are definitions accidentally placed in headers in a way that causes multiple-definition errors?
- [ ] Are include directories, namespaces, and library dependencies configured consistently?
- [ ] Does a clean build reproduce the issue, or is a stale object file hiding a dependency problem?

## Static Analysis

- [ ] What warnings or analyzer findings appear, and which are relevant to the defect?
- [ ] Are there warnings about uninitialized values, unsafe conversions, unreachable code, or suspicious conditions?
- [ ] Do ownership or lifetime warnings indicate a possible leak or dangling reference?
- [ ] Can I enable useful compiler warnings or run an available static analyzer?
- [ ] Have I addressed the underlying cause rather than merely suppressing a warning?

## Testing After Applying a Fix

- [ ] Does the project compile and link successfully with its expected C++17 settings?
- [ ] Does the original failure scenario now behave as expected?
- [ ] Have I tested normal, boundary, invalid, and empty inputs relevant to the change?
- [ ] Do existing tests still pass, and should a regression test be added?
- [ ] Have I checked that related application functionality remains unchanged?
- [ ] Can I reproduce the original failure before the fix and confirm it is resolved afterward?
- [ ] Have I recorded the exact build and test commands and their actual results?
