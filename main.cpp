#include <iostream>

#include "connect_pool.hpp"

//测试连接池性能
int main() {
    auto begin_time = std::clock();
    for (int i = 0; i < 300; ++i) {
        // MySql mysql;
        // mysql.connect("127.0.0.1", 3306, "root", "123456", "chat");
        // mysql.update("insert into user(name, age, sex) values(\"zhang san\", 18, \"male\")");
        auto sp = ConnectPool::GetInstance().GetConnection();  
        sp->update("insert into user(name, age, sex) values(\"zhang san\", 18, \"male\")");
    }
    std::cout << std::clock() - begin_time << std::endl;
}

//不是用连接池：1279212
//使用连接池：70986