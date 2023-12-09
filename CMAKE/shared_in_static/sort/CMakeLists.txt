cmake_minimum_required(VERSION 3.13)
project(sort)

# 搜索源文件
aux_source_directory(./ SRC)
include_directories(${HEADPATH})
link_directories(${LIBPATH})
# 链接CALCLIB
link_libraries(${CALCLIB})
add_library(${SORTLIB} STATIC ${SRC})
target_link_libraries(${SORTLIB} ${CALCLIB})