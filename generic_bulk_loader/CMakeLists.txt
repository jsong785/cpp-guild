cmake_minimum_required(VERSION 3.5.1)
project(generic_bulk_loader VERSION 1.0 LANGUAGES CXX)

find_package(Catch REQUIRED)
add_executable(generic_bulk_loader 
               main.cpp 
               SnowflakeLocalStage.cpp
               TestSnowflakeLocalStage.cpp)
set_property(TARGET generic_bulk_loader PROPERTY CXX_STANDARD 14)
target_link_libraries(generic_bulk_loader Catch)
