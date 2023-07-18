
#include "ConnectionPool.h"

// 线程安全的懒汉单例函数接口
ConnectionPool* ConnectionPool::getConnectionPool()
{
	static ConnectionPool pool; 
	return &pool;
}


// 去掉字符串前后的空格
void ConnectionPool::Trim(std::string& src_buf){
    int idx = src_buf.find_first_not_of(' ');
        if(idx != -1){
            // 说明字符串前面有空格
            src_buf = src_buf.substr(idx, src_buf.size() - idx);
        }
        // 去掉字符后面多余的空格
        idx = src_buf.find_last_not_of(' ');
        if(idx != -1){
            // 说明字符串前面有空格
            src_buf = src_buf.substr(0, idx + 1);
        }
}

// 从配置文件中加载配置项
bool ConnectionPool::loadConfigFile()
{
	FILE *pf = fopen("mysql.conf", "r");
	if(pf == nullptr){
        std::cout<< "mysql.ini is not exist!" <<std::endl;
        exit(EXIT_FAILURE);
    }
    while (!feof(pf))
    {
        char buf[512] = {0};
        fgets(buf, 512, pf);
        std::string read_buf(buf);
        Trim(read_buf);
        // 判断#的注释或者为空行
        if(read_buf[0] == '#' || read_buf.empty()) continue;

        // 解析配置项
        int idx = read_buf.find('=');
        if(idx == -1){
            // 配置项不合法
            continue;
        }
        std::string key;
        std::string value;
        key = read_buf.substr(0, idx);
        Trim(key);
        // 处理127.0.0.1\n
        int endidx = read_buf.find('\n', idx);
        value = read_buf.substr(idx + 1, endidx - idx - 1);
        Trim(value);
        m_configMap.insert({key, value});
	}
	ip_ = m_configMap["ip"];
	port_ = atoi(m_configMap["port"].c_str());
	username_ = m_configMap["username"];
	password_ = m_configMap["password"];
	dbname_ = m_configMap["dbname"];
	initSize_ = atoi(m_configMap["initSize"].c_str());
	maxSize_ = atoi(m_configMap["maxSize"].c_str());
	maxIdleTime_ = atoi(m_configMap["maxIdleTime"].c_str());
	connectionTimeout_ = atoi(m_configMap["connectionTimeout"].c_str());
	return true;
}


// 连接池的构造
ConnectionPool::ConnectionPool()
{
	// 加载配置项了
	if (!loadConfigFile()) return;
	

	// 创建初始数量的连接
	for (int i = 0; i < initSize_; ++i)
	{
		Connection *p = new Connection();
		if(!p->connect(ip_, port_, username_, password_, dbname_)){
			LOG("Connect Fail!");
		}
		p->refreshAliveTime(); // 刷新一下开始空闲的起始时间
		connectionQue_.push(p);
		connectionCnt_++;
	}
	running_ = true;
	// 启动一个新的线程，作为连接的生产者 linux thread => pthread_create
	thread produce(std::bind(&ConnectionPool::produceConnectionTask, this));
	produce.detach();

	// 启动一个新的定时线程，扫描超过maxIdleTime时间的空闲连接，进行对于的连接回收
	thread scanner(std::bind(&ConnectionPool::scannerConnectionTask, this));
	scanner.detach();
}

ConnectionPool::~ConnectionPool(){
	running_ = false;
	unique_lock<mutex> lock(queueMutex_);
	while(!connectionQue_.empty()){
		auto pconn = connectionQue_.front(); 
		connectionQue_.pop();
		delete pconn;
	}
}

// 运行在独立的线程中，专门负责生产新连接
void ConnectionPool::produceConnectionTask()
{
	while(running_){
		unique_lock<mutex> lock(queueMutex_);

		// 队列不空，此处生产线程进入等待状态
		if(!cv_is_empty.wait_for(lock, chrono::milliseconds(connectionTimeout_), [this](){return connectionQue_.empty(); }))
			continue;
		
		// 连接数量没有到达上限，继续创建新的连接
		if (connectionCnt_ < maxSize_)
		{
			Connection *p = new Connection();
			p->connect(ip_, port_, username_, password_, dbname_);
			p->refreshAliveTime(); // 刷新一下开始空闲的起始时间
			connectionQue_.push(p);
			++connectionCnt_;
		}

		// 通知消费者线程，可以消费连接了
		cv_not_empty.notify_all();
	}
}

// 给外部提供接口，从连接池中获取一个可用的空闲连接
shared_ptr<Connection> ConnectionPool::getConnection()
{
	unique_lock<mutex> lock(queueMutex_);
	while(!cv_not_empty.wait_for(lock, chrono::milliseconds(connectionTimeout_), [this](){return !connectionQue_.empty();})){
		LOG("time out! ...getting free conn failed!");
	}

	/*
	shared_ptr智能指针析构时，会把connection资源直接delete掉，相当于
	调用connection的析构函数，connection就被close掉了。
	这里需要自定义shared_ptr的释放资源的方式，把connection直接归还到queue当中
	*/
	shared_ptr<Connection> sp(connectionQue_.front(), 
		[=](Connection *pcon) {
		// 这里是在服务器应用线程中调用的，所以一定要考虑队列的线程安全操作
		unique_lock<mutex> lock(this->queueMutex_);
		pcon->refreshAliveTime(); // 刷新一下开始空闲的起始时间
		this->connectionQue_.push(pcon);
	});

	connectionQue_.pop();
	if(connectionQue_.empty())
		cv_is_empty.notify_all();  // 消费完连接以后，通知生产者线程检查一下，如果队列为空了，赶紧生产连接
	
	return sp;
}

// 扫描超过maxIdleTime时间的空闲连接，进行对于的连接回收
void ConnectionPool::scannerConnectionTask()
{
	for (;;)
	{
		// 通过sleep模拟定时效果
		this_thread::sleep_for(chrono::seconds(maxIdleTime_));

		// 扫描整个队列，释放多余的连接
		unique_lock<mutex> lock(queueMutex_);
		while (connectionCnt_ > initSize_)
		{
			Connection *p = connectionQue_.front();
			if (p->getAliveeTime() >= (maxIdleTime_ * 1000))
			{
				connectionQue_.pop();
				connectionCnt_--;
				delete p; // 调用~Connection()释放连接
			}
			else break; // 队头的连接没有超过_maxIdleTime，其它连接肯定没有
		}
	}
}