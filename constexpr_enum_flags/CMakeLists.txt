cmake_minimum_required(VERSION 3.5.1)
project(constexpr_enum_flags VERSION 1.0 LANGUAGES CXX)

add_executable(constexpr_enum_flags
               enum_flags.hpp
               TestEnumFlags.cpp)
set_property(TARGET constexpr_enum_flags PROPERTY CXX_STANDARD 17)
