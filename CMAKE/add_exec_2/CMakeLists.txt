cmake_minimum_required(VERSION 3.13)
project(test)
# 将工程目录（可认为是CMakeLists所在目录下）的所有源文件保存到变量SRC中
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
# 与上一行作用类似，将CMAKE_CURRENT_SOURCE_DIR目录下的所有源文件保存到变量SRC中
# file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# 定义头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)
# 定义可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(a.out ${SRC})