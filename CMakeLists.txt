cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 14)

project(se_sandbox)

add_compile_options(-Wall -Wextra -Werror -O0)

include_directories(.)

add_subdirectory(list)
add_subdirectory(mm)
add_subdirectory(hash)
