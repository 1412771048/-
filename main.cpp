#include <iostream>

#include "connect_pool.hpp"

//测试连接池性能
int main() {
    
    auto sp = ConnectPool::GetInstance().GetConnection();  
    // sp->update("insert into user values('li si', '18', 'on')");
    // std::string name = "zhang san";
    // char buf[1024] = {0};
    // snprintf(buf, sizeof(buf), "update user set state = 'off' where name = '%s'", name.c_str());
    // sp->update(buf);
    auto res = sp->query("select * from user");
    if (res) {//query执行成功，查看结果
        MYSQL_ROW row;
        int sign = 0;
        while (row = mysql_fetch_row(res)) {
            std::cout << "第" << ++sign << "条:" << std::endl;
            std::cout << "name: " << row[0] << std::endl;
            std::cout << "password: " << row[1] << std::endl;
            std::cout << "state: " << row[2] << std::endl;
        }
        std::cout << "总共查到" << sign << "条数据" << std::endl;
        mysql_free_result(res);
    } 
    else {//query函数执行失败
        std::cout << "query failed!" << std::endl;
    }
}

//不是用连接池：1279212
//使用连接池：70986