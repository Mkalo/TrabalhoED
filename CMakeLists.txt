cmake_minimum_required(VERSION 2.8)

project(TrabalhoED C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

add_executable(trabalho main.c list.c node.c graph.c)
include_directories(${CMAKE_CURRENT_LIST_DIR})
