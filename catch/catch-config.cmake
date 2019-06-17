cmake_minimum_required(VERSION 3.5.1)
project(SinglyLinkedList VERSION 1.0 LANGUAGES CXX)

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE ${CMAKE_CURRENT_LIST_DIR})
