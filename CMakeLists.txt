cmake_minimum_required(VERSION 3.5)
project(MyProject)

add_executable(
    aizo_ii 
    src/main.cpp 
    src/menus.h 
    src/utils/utils.cpp 
    src/utils/fileLoader.cpp 
    src/struct/Array.h 
    src/struct/EdgeHeap.cpp 
    src/struct/EdgeHeap.h 
    src/struct/Path.cpp 
    src/struct/Path.h 
    src/struct/PathEdge.h 
    src/graph/IMGraph.cpp 
    src/graph/ALGraph.cpp 
    src/algorithm/MST.cpp
    src/algorithm/SP.cpp
    src/algorithm/MF.cpp
    )

target_include_directories(aizo_ii PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/src
${CMAKE_CURRENT_SOURCE_DIR}/src/graph 
${CMAKE_CURRENT_SOURCE_DIR}/src/utils
${CMAKE_CURRENT_SOURCE_DIR}/src/algorithm
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
