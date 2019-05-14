cmake_minimum_required(VERSION 3.5.1)
project(LRUCache VERSION 1.0 LANGUAGES CXX)

add_executable(LRUCache
               LRUCache.cpp
               main.cpp
               LRUCacheTest.cpp)

set_property(TARGET LRUCache PROPERTY CXX_STANDARD 14)
