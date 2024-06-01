cmake_minimum_required(VERSION 3.5)
project(MyProject)

add_executable(scnd_project main.cpp menus.h utils.h UndirectedIMGraph.h ALGraph.h Edges.h)

target_include_directories(scnd_project PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
