cmake_minimum_required(VERSION 2.8)
set (CMAKE_BUILD_TYPE debug)

project(vtkGui)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(vtkGui 
		main.cpp 
		myChartXY.cpp
		Fl_GUI/Fl_Window.cpp
		Fl_GUI/Fl.cpp
		)
target_link_libraries(vtkGui ${VTK_LIBRARIES})



###################################################
include(CTest)
enable_testing()

add_test(test1 vtkGui 11 22)
