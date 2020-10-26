cmake_minimum_required(VERSION 3.5.1)
project(functional VERSION 1.0 LANGUAGES CXX)

add_executable(function_object
               main.cpp
               catch.hpp
               function_object.hpp
               function_object.cpp)
set_property(TARGET function_object PROPERTY CXX_STANDARD 17)
target_link_libraries(function_object)
