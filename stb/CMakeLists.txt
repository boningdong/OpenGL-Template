cmake_minimum_required(VERSION 2.8)

add_library(stb stb_image.h stb_image.cpp)
target_include_directories(stb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


