cmake_minimum_required(VERSION 2.8)

project(TrabalhoED C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -fsanitize=address -fno-omit-frame-pointer -Wall -Werror")

add_executable(trabalho list.c node.c graph.c menu.c main.c)
include_directories(${CMAKE_CURRENT_LIST_DIR})
