cmake_minimum_required(VERSION 3.5.1)
project(SinglyLinkedList VERSION 1.0 LANGUAGES CXX)

add_executable(SinglyLinkedList
               main.cpp
               SinglyLinkedListTest.cpp)

set_property(TARGET SinglyLinkedList PROPERTY CXX_STANDARD 14)
