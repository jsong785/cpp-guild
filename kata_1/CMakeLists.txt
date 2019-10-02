cmake_minimum_required(VERSION 3.5.1)
project(kata_1 VERSION 1.0 LANGUAGES CXX)

find_package(Catch REQUIRED)
add_executable(kata_1 
               main.cpp 
			   test_kata.cpp)
set_property(TARGET kata_1 PROPERTY CXX_STANDARD 14)
target_link_libraries(kata_1 Catch)
