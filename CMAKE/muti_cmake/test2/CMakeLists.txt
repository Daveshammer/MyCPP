cmake_minimum_required(VERSION 3.13)
project(test1)

# 搜索源文件
aux_source_directory(./ SRC)
include_directories(${HEADPATH})
link_directories(${LIBPATH})
# 静态库链接，也可以使用最后一行target_link_libraries(${APPNAME2} ${SORTLIB})
# link_libraries(${SORTLIB})
set(EXECUTABLE_OUTPUT_PATH ${EXECPATH})
add_executable(${APPNAME2} ${SRC})
target_link_libraries(${APPNAME2} ${SORTLIB})