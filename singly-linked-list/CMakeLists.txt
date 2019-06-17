cmake_minimum_required(VERSION 3.5.1)
project(SinglyLinkedList VERSION 1.0 LANGUAGES CXX)

find_package(catch REQUIRED HINTS ../catch/)
add_executable(SinglyLinkedList
               main.cpp
               SinglyLinkedListTest.cpp)
target_link_libraries(SinglyLinkedList catch)
set_property(TARGET SinglyLinkedList PROPERTY CXX_STANDARD 14)
