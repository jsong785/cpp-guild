cmake_minimum_required(VERSION 3.5.1)
project(LRUCache VERSION 1.0 LANGUAGES CXX)

find_package(catch REQUIRED HINTS ../catch)
add_executable(LRUCache
               LRUCache.cpp
               main.cpp
               LRUCacheTest.cpp)
target_link_libraries(LRUCache catch)

set_property(TARGET LRUCache PROPERTY CXX_STANDARD 14)
