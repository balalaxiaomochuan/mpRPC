# aux_source_directory(. SRC_LIST)
set(SRC_LIST 
    mprpcapplication.cc 
    mprpcconfig.cc 
    rpcheader.pb.cc 
    rpcprovider.cc 
    mprpcchannel.cc 
    mprpccontroller.cc
    logger.cc
    zookeeperutil.cc) 
# SHARED表示生成动态库
# add_library(mprpc SHARED ${SRC_LIST})
# 不加SHARED表示生成静态库
add_library(mprpc ${SRC_LIST})
# 由于muduo_base muduo_net都是后缀为.a的静态库，所以rpc框架库只能也被编译成静态库
target_link_libraries(mprpc muduo_net muduo_base pthread zookeeper_mt)