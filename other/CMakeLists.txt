cmake_minimum_required(VERSION 3.5.1)
project(other VERSION 1.0 LANGUAGES CXX)

find_package(Catch REQUIRED)
add_executable(other
               main.cpp 
               currying.cpp)
set_property(TARGET other PROPERTY CXX_STANDARD 14)
target_link_libraries(other Catch)
