cmake_minimum_required(VERSION 3.0)#要求cmake最低的版本号
project(mymuduo) # 定义当前工程名字

# 配置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # -g 是可调试选项

#生成debug版本，可以进行gdb调试
set(CMAKE_BUILD_TYPE, "Debug")

#指定搜索的子目录
add_subdirectory(testmuduo)
