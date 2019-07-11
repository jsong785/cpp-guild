cmake_minimum_required(VERSION 3.5.1)
project(HourGlass VERSION 1.0 LANGUAGES CXX)

find_package(Catch REQUIRED)
add_executable(HourGlass main.cpp HourGlass.cpp)
set_property(TARGET HourGlass PROPERTY CXX_STANDARD 14)
target_link_libraries(HourGlass Catch)
