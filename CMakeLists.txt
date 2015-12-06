cmake_minimum_required(VERSION 2.8)

project(vtkGui)

include(CTest)
enable_testing()

add_executable(vtkGui main.cpp)

add_test(test1 vtkGui 11 22)
