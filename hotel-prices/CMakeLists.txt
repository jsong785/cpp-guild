cmake_minimum_required(VERSION 3.5.1)
project(HotelPrices VERSION 1.0 LANGUAGES CXX)

find_package(Catch REQUIRED)
add_executable(HotelPrices
               main.cpp
               HotelPricesTest.cpp)
target_link_libraries(HotelPrices Catch)
set_property(TARGET HotelPrices PROPERTY CXX_STANDARD 14)
