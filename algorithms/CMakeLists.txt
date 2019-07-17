cmake_minimum_required(VERSION 3.5.1)
project(algorithms VERSION 1.0 LANGUAGES CXX)

find_package(Catch REQUIRED)
add_executable(algorithms 
               main.cpp 
               LinkedListTest.cpp
               MatrixTest.cpp
               MostOccuringItemTest.cpp
               StringUtilsTest.cpp
               SelectionSortTest.cpp
               TreeTest.cpp)
set_property(TARGET algorithms PROPERTY CXX_STANDARD 14)
target_link_libraries(algorithms Catch)
