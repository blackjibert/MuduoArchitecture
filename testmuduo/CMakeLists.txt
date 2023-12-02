#配置头文件搜索路径
# include_directories()
#配置库文件搜索路径
# link_directories()

#设置需要编译的源文件列表
set(SRC_lIST ./muduo_server.cc)

# 设置可执行文件最终存储的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 把.指定路径下的所有源文件名字放入变量名SRC_LIST里面
# aux_source_directory(. SRC_lIST)

#通过SRC_lIST中的文件, 生成可执行文件server
add_executable(server ${SRC_lIST}) 

#server这个目标程序,需要链接muduo_net muduo_base pthread这三个库文件
target_link_libraries(server muduo_net muduo_base pthread)

#进入子目录下执行 CMakeLists.txt文件这里的1ib和tests里面都有可编译的代码文件
# add_subdirectory(lib)
# add_subdirectory(tests)