cmake_minimum_required(VERSION 3.5.1)
project(ConstexprTest VERSION 1.0 LANGUAGES CXX)

add_executable(ConstexprTest main.cpp)

set_property(TARGET ConstexprTest PROPERTY CXX_STANDARD 14)
