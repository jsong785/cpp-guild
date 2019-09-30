cmake_minimum_required(VERSION 3.5.1)
project(do_and_finish VERSION 1.0 LANGUAGES CXX)

find_package(Catch REQUIRED)
add_executable(do_and_finish 
               main.cpp 
               TestDoAndFinish.cpp)
set_property(TARGET do_and_finish PROPERTY CXX_STANDARD 14)
target_link_libraries(do_and_finish Catch)
