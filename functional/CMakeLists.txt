cmake_minimum_required(VERSION 3.5.1)
project(currying VERSION 1.0 LANGUAGES CXX)

find_package(Catch REQUIRED)
add_executable(currying
               main.cpp 
               currying.cpp)
set_property(TARGET currying PROPERTY CXX_STANDARD 14)
target_link_libraries(currying Catch)
