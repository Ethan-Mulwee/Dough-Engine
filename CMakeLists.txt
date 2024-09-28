cmake_minimum_required(VERSION 3.10) 

project(main)


file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(main main.cpp ${SRC_FILES})
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main PUBLIC /usr/local/lib/libraylib.so)