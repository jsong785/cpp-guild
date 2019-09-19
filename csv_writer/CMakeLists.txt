cmake_minimum_required(VERSION 3.5.1)
project(csv_writer VERSION 1.0 LANGUAGES CXX)

find_package(Catch REQUIRED)
add_executable(csv_writer 
               main.cpp 
               CsvWriter.cpp
               TestCsvWriter.cpp)
set_property(TARGET csv_writer PROPERTY CXX_STANDARD 14)
target_link_libraries(csv_writer Catch)
