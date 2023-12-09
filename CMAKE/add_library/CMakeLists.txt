cmake_minimum_required(VERSION 3.13)
project(test)
# 将工程目录（可认为是CMakeLists所在目录下）的所有源文件保存到变量SRC中
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
# 与上一行作用类似，将CMAKE_CURRENT_SOURCE_DIR目录下的所有源文件保存到变量SRC中
# file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# 定义头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)
# 设置库文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 定义库文件输出路径，SHARED表示动态库，STATIC表示静态库
add_library(calc SHARED ${SRC})