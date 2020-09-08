cmake_minimum_required(VERSION 3.5.1)
project(algorithms VERSION 1.0 LANGUAGES CXX)

add_executable(algorithms 
               catch.hpp
               main.cpp 
               LinkedListTest.cpp
               MatrixTest.cpp
               MostOccuringItemTest.cpp
               Graph.hpp
               GraphTest.cpp
               StringUtilsTest.cpp
               SortTest.cpp
               TreeTest.cpp)
set_property(TARGET algorithms PROPERTY CXX_STANDARD 14)
