cmake_minimum_required(VERSION 3.5.1)
project(article VERSION 1.0 LANGUAGES CXX)

#find_package(Catch REQUIRED)
add_executable(article
               main.cpp 
               test.cpp)
set_property(TARGET article PROPERTY CXX_STANDARD 17)
#target_link_libraries(article Catch)
