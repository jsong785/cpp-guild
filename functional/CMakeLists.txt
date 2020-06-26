cmake_minimum_required(VERSION 3.5.1)
project(functional VERSION 1.0 LANGUAGES CXX)

#find_package(Catch REQUIRED)
add_executable(functional
               fmap.hpp
               fmap.cpp
               main.cpp 
               monads.cpp
               memoize.cpp
               currying.cpp
               recursion.cpp
               maybe_monad.cpp
               reverse_polish_notation.cpp
               reverse_polish_notation_constexpr.cpp
               shortest_route.hpp
               shortest_route.cpp
               string.cpp)
set_property(TARGET functional PROPERTY CXX_STANDARD 17)
target_link_libraries(functional)
