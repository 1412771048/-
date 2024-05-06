为提高mysql的访问性能，可增加连接池，为什么他能提高性能：
mysql是基于C/S架构，从客户端到服务器，一条sql的执行流程：tcp三次握手->mysql连接认证->执行sql->关闭mysql连接->tcp四次挥手
每次数据库都需要这5步太耗时，连接池缓存连接，后续直接用，5步变1步
连接池包含：认证所需的信息、初始连接数、最大连接数、最大空闲时间(超过则回复连接数为初始连接数)、连接超时时间(当连接数达到maxsize，就会等待一段时间不断的尝试获取连接，超时则算连结失败)

连接池单例；空闲连接维护在一个加锁队列里；单生产者多消费者模型
懒汉式：第一次运行时再初始化，我们写的都是懒汉式

std::atomic<T> a  原子类型，T得是基本类型，因为它只能保证单个变量的线程安全
