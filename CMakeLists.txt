cmake_minimum_required(VERSION 3.5)
project(MyProject)

add_executable(
    scnd_project 
    src/main.cpp 
    src/menus.h 
    utils/utils.cpp 
    graph/IMGraph.cpp 
    graph/ALGraph.cpp 
    graph/Edges.cpp
    algorithm/MST.cpp
    )

target_include_directories(scnd_project PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/graph 
${CMAKE_CURRENT_SOURCE_DIR}/utils
${CMAKE_CURRENT_SOURCE_DIR}/algorithm
)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
