#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <atomic>
#include <thread>
#include "mysql.hpp"
#include "SimpleIni.h"

//连接池类
class ConnectPool {
public:
    ConnectPool(const ConnectPool&) = delete;
    ConnectPool(ConnectPool&&) = delete;
    ConnectPool& operator=(const ConnectPool&) = delete;
    ConnectPool& operator=(ConnectPool&&) = delete;
    ~ConnectPool() = default;

    static ConnectPool& GetInstance();
private:
    ConnectPool();               // 构造函数私有化,单例
    bool LoadConfig();           // 加载配置文件

    std::string ip_;             // mysql的ip
    uint16_t port_;              // mysql的port
    std::string username_;       // 登录mysql的用户名 
    std::string password_;       // 登录mysql的密码
    std::string database_;       // 要访问的数据库名
    uint32_t initSize_;          // 初始连接数
    uint32_t maxSize_;           // 最大连接数
    uint16_t maxIdleTime_;       // 最大空闲时间 s
    int connectTimeout_;         // 获取连接的超时时间 ms

    std::queue<MySql*> connQue_;       // 存储空闲连接的队列
    std::mutex queueMtx_;              // 保护队列的互斥锁
    std::atomic<uint16_t> connectCnt_; //记录连接的总数，且是线程安全的
};

ConnectPool& ConnectPool::GetInstance() {
    static ConnectPool pool; //静态局部变量的初始化是线程安全的
    return pool;
}

bool ConnectPool::LoadConfig() {
    CSimpleIniA ini;
    if (ini.LoadFile("mysql.conf") < 0) {
        return false;
    }
    ip_ = ini.GetValue("mysql", "ip");
    port_ = std::stoi(ini.GetValue("mysql", "port"));
    username_ = ini.GetValue("mysql", "username");
    password_ = ini.GetValue("mysql", "password");
    database_ = ini.GetValue("mysql", "database");
    initSize_ = std::stoi(ini.GetValue("mysql", "initSize"));
    maxSize_ = std::stoi(ini.GetValue("mysql", "maxSize"));
    maxIdleTime_ = std::stoi(ini.GetValue("mysql", "maxIdleTime"));
    connectTimeout_ = std::stoi(ini.GetValue("mysql", "connectTimeout"));
    return true;
}

ConnectPool::ConnectPool() {
    if (LoadConfig()) {
        //创建初始数量的连接
        for (int i = 0; i < initSize_; i++) {
            MySql* p = new MySql;
            p->connect(ip_, port_, username_, password_, database_);
            connQue_.push(p);
            ++connectCnt_;
        }
    }

}