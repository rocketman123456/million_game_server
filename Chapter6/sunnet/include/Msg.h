#pragma once
#include <memory>
using namespace std; 

#include "pthread_spin.h"

//消息基类
class BaseMsg {
public:
    enum TYPE {          //消息类型
        SERVICE = 1, 
        SOCKET_ACCEPT = 2,
        SOCKET_RW = 3,
    }; 
    uint8_t type;           //消息类型
    char load[999999]{};    //用于检测内存泄漏
    virtual ~BaseMsg(){};
};

//服务间消息
class ServiceMsg : public BaseMsg  {
public: 
    uint32_t source;        //消息发送方
    shared_ptr<char> buff;  //消息内容
    size_t size;            //消息内容大小
};

//新连接
class SocketAcceptMsg : public BaseMsg {
public: 
    int listenFd;
    int clientFd;
};

//可读可写
class SocketRWMsg : public BaseMsg {
public: 
    int fd;
    bool isRead = false;
    bool isWrite = false;
};