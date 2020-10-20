cmake_minimum_required(VERSION 3.5.1)
project(templates VERSION 1.0 LANGUAGES CXX)

#find_package(Catch REQUIRED)
add_executable(templates
               main.cpp 
               TestVirtual.cpp
               TestOverload.cpp
               TestFibonacci.cpp
               TestNested.cpp
               TestSfinae.cpp
               TestTuple.cpp
               TestVariadic.cpp)
set_property(TARGET templates PROPERTY CXX_STANDARD 17)
#target_link_libraries(templates Catch)
