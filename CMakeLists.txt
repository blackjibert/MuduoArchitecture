cmake_minimum_required (VERSION 3.0)#要求cmake最低的版本号
project (muduo_demo) # 定义当前工程名字

#设置编译选项
set(CMAKE_CXX_FLAGS ${ICMAKE_CXX_FLAGS} -g) #-g是可调试

#指定搜索的子目录
add_subdirectory(testmuduo)