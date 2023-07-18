#include <iostream>
using namespace std;
#include "Connection.h"
#include "ConnectionPool.h"

int main()
{

	clock_t begin = clock();
	
	// thread t1([]() {
	// 	ConnectionPool *cp = ConnectionPool::getConnectionPool();
	// 	for (int i = 0; i < 2500; ++i)
	// 	{
	// 		char sql[1024] = { 0 };
	// 		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	// 			"zhang san", 20, "male");
	// 		shared_ptr<Connection> sp = cp->getConnection();
	// 		sp->update(sql);
	// 		// Connection conn;
	// 		// char sql[1024] = { 0 };
	// 		// sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	// 		// 	"zhang san", 20, "male");
	// 		// conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	// 		// conn.update(sql);
	// 	}
	// });
	// thread t2([]() {
	// 	ConnectionPool *cp = ConnectionPool::getConnectionPool();
	// 	for (int i = 0; i < 2500; ++i)
	// 	{
	// 		char sql[1024] = { 0 };
	// 		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	// 			"zhang san", 20, "male");
	// 		shared_ptr<Connection> sp = cp->getConnection();
	// 		sp->update(sql);
	// 		// Connection conn;
	// 		// char sql[1024] = { 0 };
	// 		// sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	// 		// 	"zhang san", 20, "male");
	// 		// conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	// 		// conn.update(sql);
	// 	}
	// });
	// thread t3([]() {
	// 	ConnectionPool *cp = ConnectionPool::getConnectionPool();
	// 	for (int i = 0; i < 2500; ++i)
	// 	{
	// 		char sql[1024] = { 0 };
	// 		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	// 			"zhang san", 20, "male");
	// 		shared_ptr<Connection> sp = cp->getConnection();
	// 		sp->update(sql);
	// 		// Connection conn;
	// 		// char sql[1024] = { 0 };
	// 		// sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	// 		// 	"zhang san", 20, "male");
	// 		// conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	// 		// conn.update(sql);
	// 	}
	// });
	// thread t4([]() {
	// 	ConnectionPool *cp = ConnectionPool::getConnectionPool();
	// 	for (int i = 0; i < 2500; ++i)
	// 	{
	// 		char sql[1024] = { 0 };
	// 		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	// 			"zhang san", 20, "male");
	// 		shared_ptr<Connection> sp = cp->getConnection();
	// 		sp->update(sql);
	// 		// Connection conn;
	// 		// char sql[1024] = { 0 };
	// 		// sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	// 		// 	"zhang san", 20, "male");
	// 		// conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	// 		// conn.update(sql);
	// 	}
	// });

	// t1.join();
	// t2.join();
	// t3.join();
	// t4.join();

	

#if 1
	for (int i = 0; i < 10; ++i)
	{
		// Connection conn;
		// char sql[1024] = { 0 };
		// sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
		// 	"zhang san", 20, "male");
		// conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
		// conn.update(sql);
		ConnectionPool *cp = ConnectionPool::getConnectionPool();
		shared_ptr<Connection> sp = cp->getConnection();
		char sql[1024] = { 0 };
		sprintf(sql, "insert into User(name,password,state) values('%s','%s','%s')",
			"test", "zxc", "offline");
		sp->update(sql);
	}
#endif
	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;
	cout << "test end!" << endl;
	return 0;
}
