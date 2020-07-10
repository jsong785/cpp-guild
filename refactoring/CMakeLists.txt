cmake_minimum_required(VERSION 3.5.1)
project(refactor VERSION 1.0 LANGUAGES CXX)

#find_package(Catch REQUIRED)
add_executable(refactor
               legacy.cpp
               legacy.h
               new.cpp
               new.h
               main.cpp
               tests.cpp)
set_property(TARGET refactor PROPERTY CXX_STANDARD 17)
target_link_libraries(refactor)
