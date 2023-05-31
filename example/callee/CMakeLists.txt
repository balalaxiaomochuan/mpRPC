# set(SRC_LIST userservice.cc ../user.pb.cc)
set(SRC_LIST friendservice.cc ../friend.pb.cc)
add_executable(provider ${SRC_LIST})

# 生成provider可执行文件，需要链接mprpc（我们所写的框架）和protobuf
target_link_libraries(provider mprpc protobuf)