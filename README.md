# ConnectionPool

## 内容列表

- [背景](#背景)
- [设计思路](#设计思路)
- [数据库连接池的大小](#数据库连接池的大小)
- [安装说明](#安装说明)
- [压力测试](#压力测试)

## 背景
+ 本项目是小型的数据库连接池，旨在提高MySQL数据库的访问瓶颈。

## 设计思路
ConnectionPool类采用单例模式，保证全局只有一个ConnectionPool类对象；以及保存一个生产者-消费者队列，用于创建更多的连接、回收多余的连接。
**在构造函数ConnectionPool()中**
- 首先会读取配置文件，获取连接MySQL相关的配置信息；
- 而后会建立指定数量的连接并保存到连接队列中；
- 启动两个守护线程：produceConnectionTask和scannerConnectionTask。


**getConnection()**
getConnection()用于返回给用户可用的连接。
- 首先获取队列的互斥锁，然后将对头连接用智能指针包裹返回给用户，这里有个非常好的设计。就是我们还给智能指针传入了一个删除器，当用户用完连接之后，引用计数为0，在删除器内将连接再插入到连接队列的队尾。

**scannerConnectionTask**
定期扫描超过maxIdleTime时间的空闲连接，进行对于的连接回收。流程：
- 如果当前连接数大于初始连接数，那么就从队头开始扫描，如果刷新时间已经大于超时时间，那么就回收；
- 如果没有，那么终止循环，因为队头是最先进来的，如果队头没有超时，后面一定没有超时。

**produceConnectionTask**
就是一个生产者线程。

## 数据库连接池的大小
- 首先需要说明的是，数据库连接池的大小在最小连接数与最大连接数之间。
- 如果数据库连接请求超过最大连接量时，后面的请求将加入到等待队列中；
- 如果数据库的最小连接数过小，那么最先请求的会获利，后面的由于需要重新创建连接而有延迟。
- 如何确定以上两个参数？其实最大连接数并不是越大越好，因为假设我们将最大连接数设置成200，对数据库服务器来说就有200个并发通道，这是相当可怕的系统负载，并且由于并发量高，还会增加SQL之间抢占锁的频率，进一步降低系统并发量。
- 因此，对于具体数值的设定，还要靠实际压测结果。对于数据库服务器，平均数据库处理时长在2ms以下的话，最大连接数设为10可达到TPS到5000。

## 压力测试

## 安装说明

开发环境：Ubuntu VsCode

编译器：g++

编译工具：CMake

编程语言：C++
