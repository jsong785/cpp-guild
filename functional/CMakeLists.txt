cmake_minimum_required(VERSION 3.5.1)
project(functional VERSION 1.0 LANGUAGES CXX)

find_package(Catch REQUIRED)
add_executable(functional
               main.cpp 
               currying.cpp
               string.cpp)
set_property(TARGET functional PROPERTY CXX_STANDARD 14)
target_link_libraries(functional Catch)
