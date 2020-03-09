cmake_minimum_required(VERSION 3.5.1)
project(functional VERSION 1.0 LANGUAGES CXX)

#find_package(Catch REQUIRED)
add_executable(functional
               main.cpp 
               memoize.cpp
               currying.cpp
               recursion.cpp
               maybe_monad.cpp
               string.cpp)
set_property(TARGET functional PROPERTY CXX_STANDARD 17)
target_link_libraries(functional)
