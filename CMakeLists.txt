cmake_minimum_required(VERSION 2.8)

project(vtkGui)
set (cmake_build_type debug)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(vtkGui main.cpp)
target_link_libraries(vtkGui ${VTK_LIBRARIES})



###################################################
include(CTest)
enable_testing()

add_test(test1 vtkGui 11 22)
