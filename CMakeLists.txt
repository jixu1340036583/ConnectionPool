cmake_minimum_required(VERSION 3.0)
project(ConnectionPool)

# 编译选项 设置可调试
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 配置项目库文件输出的路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 配置项目编译头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 配置项目库文件搜索路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(src)
add_subdirectory(test)