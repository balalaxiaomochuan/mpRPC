#include "mprpcconfig.h"
#include <iostream>

// 负责解析加载配置文件
void MprpcConfig::LoadConfigFile(const char* config_file){
    FILE *pf = fopen(config_file, "r");
    if(pf == nullptr){
        printf("%s is not exist!\n", config_file);
        exit(EXIT_FAILURE);
    }

    // 1.注释 2.正确的配置项 =    3.去掉开头多余的空格
    while(!feof(pf)){
        char buf[512] = {0};
        fgets(buf, 512, pf);
        
        // 去掉字符串多余的空格
        std::string read_buf(buf);
        Trim(read_buf);
        

        // 去除注释
        if(read_buf[0] == ' ' || read_buf.empty()){
            continue;
        }

        // 读取键值对，如rpcserverport = 8000
        std::string key;
        std::string value;
        int idx = read_buf.find_first_of('=');
        key = read_buf.substr(0, idx);
        Trim(key);
        int endidx = read_buf.find('\n', idx);

        value = read_buf.substr(idx+1, endidx-idx-1);
        Trim(value);
        m_configMap.insert({key, value});
    }

}

void MprpcConfig::Trim(std::string& src_buf){
    int idx = src_buf.find_first_not_of(' ');

    if(idx != -1){
        src_buf = src_buf.substr(idx, src_buf.size() - idx);
    }

    // 去掉后面多余的空格
    idx = src_buf.find_last_not_of(' ');
    if(idx != -1){
        src_buf = src_buf.substr(0, idx+1);
    }
}

// 查询配置项信息
std::string MprpcConfig::Load(const std::string &key){
    auto it = m_configMap.find(key);
    if(it == m_configMap.end()){
        return "";
    }
    return it->second;
}