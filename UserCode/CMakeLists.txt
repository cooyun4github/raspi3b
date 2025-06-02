# 如果没有需要安装cmake：sudo apt-get install cmake

cmake_minimum_required(VERSION 3.10)
project(cy_pin4 C)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)

# 添加子目录
#add_subdirectory(pin4)
#add_subdirectory(util)

# 包含头文件路径
include_directories(${PROJECT_SOURCE_DIR}/pin4 ${PROJECT_SOURCE_DIR}/utils)

# 定义源文件列表
set(SOURCES
    pin4/pin4.c
)

# 添加可执行程序
add_executable(pin4 ${SOURCES})