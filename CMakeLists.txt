# 使用CMake Tools插件（可选，如果这个项目去到一个没有这个插件的机器也同样可以生成项目）
# include(CMakeToolsHelpers OPTIONAL)

# CMake 最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 项目名称
project(AGCC)

#设置编译器
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

#c++11标准
add_definitions(-std=c++11)

#Debug或者Release -DCMAKE_BUILD_TYPE=Release 或者 -DCMAKE_BUILD_TYPE=Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# 查找头文件
include_directories(./include)

# 查找src目录下的所有源文件
# 并将名称保存到 DIR_ROOT_SRCS变量
aux_source_directory(./src DIR_ROOT_SRCS)

# 指定生成目标
add_executable(AGCC ${DIR_ROOT_SRCS})
