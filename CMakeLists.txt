cmake_minimum_required(VERSION 3.10) 

project(hello)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(hello main.cpp ${SRC_FILES})
target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/dough)