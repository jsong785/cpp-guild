cmake_minimum_required(VERSION 3.5.1)
project(SingleLinkedList VERSION 1.0 LANGUAGES CXX)

add_executable(SingleLinkedList
               SingleLinkedList.cpp
               main.cpp
               SingleLinkedListTest.cpp)

set_property(TARGET SingleLinkedList PROPERTY CXX_STANDARD 14)
