cmake_minimum_required(VERSION 3.13)
project(sort)

# 搜索源文件
aux_source_directory(./ SRC)
include_directories(${HEADPATH})
# 设置静态库生成目录
set(LIBRARY_OUTPUT_PATH ${LIBPATH})
link_directories(${LIBPATH})
# 链接CALCLIB
add_library(${SORTLIB} STATIC ${SRC})
target_link_libraries(${SORTLIB} ${CALCLIB})
