cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 14)

project(se_sandbox)

include_directories(.)

add_subdirectory(list)
add_subdirectory(mm)
add_subdirectory(hash)
add_subdirectory(sort)
