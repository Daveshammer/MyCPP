# cmake_minimum_required(VERSION 3.13)
# project(test)
# add_executable(a.out add.cpp div.cpp mult.cpp sub.cpp main.cpp)

# cmake_minimum_required(VERSION 3.13)
# project(test)
# set(SRC add.cpp div.cpp mult.cpp sub.cpp main.cpp)
# # 定义可执行文件输出路径
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# # 指定语言标准
# set(CMAKE_CXX_STANDARD 17)
# add_executable(a.out ${SRC})

cmake_minimum_required(VERSION 3.13)
project(test)
# 将工程目录（可认为是CMakeLists所在目录下）的所有源文件保存到变量SRC中
aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
# 与上一行作用类似，将CMAKE_CURRENT_SOURCE_DIR目录下的所有源文件保存到变量SRC中
# file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# 定义可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(a.out ${SRC})