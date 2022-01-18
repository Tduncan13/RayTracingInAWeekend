cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11) 

project(raytrace VERSION 1.0)
add_executable(raytrace main.cc)

target_include_directories(raytrace PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
