cmake_minimum_required(VERSION 3.5.1)
project(constexpr_shopping_cart VERSION 1.0 LANGUAGES CXX)

add_executable(constexpr_shopping_cart
               shopping_cart.hpp
               TestShoppingCart.cpp)
set_property(TARGET constexpr_shopping_cart PROPERTY CXX_STANDARD 17)
