cmake_minimum_required(VERSION 3.13)
project(clac)

# 搜索源文件
aux_source_directory(./ SRC)
include_directories(${HEADPATH})
# 设置库生成目录
set(LIBRARY_OUTPUT_PATH ${LIBPATH})
add_library(${CALCLIB} SHARED ${SRC})
