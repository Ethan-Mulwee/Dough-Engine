cmake_minimum_required(VERSION 3.10) 

project(Phyiscs)


file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(Main-DEMO demos/maindemo.cpp ${SRC_FILES})
target_include_directories(Main-DEMO PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Main-DEMO PUBLIC /usr/local/lib/libraylib.so)
#file(GLOB DEMO_SOURCES demo/*.cpp)
#foreach(testsourcefile ${DEMO_SOURCES})
#    get_filename_component( testname ${testsourcefile} NAME_WE )
#    add_executable( ${testname} ${testsourcefile} )
#    target_include_directories(Main-DEMO PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#    target_link_libraries(Main-DEMO PUBLIC /usr/local/lib/libraylib.so)
#endforeach( testsourcefile ${DEMO_SOURCES} )