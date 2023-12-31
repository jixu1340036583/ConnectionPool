-- 初始化连接池，准备测试环境
function prepare()
    -- 在这里编写连接池的初始化逻辑，可以创建连接池对象，设置连接池参数等
end

-- 清理连接池和测试环境
function cleanup()
    -- 在这里编写连接池的清理逻辑，可以释放连接池资源，关闭连接等
end

-- 初始化线程，可以设置每个线程的特定配置
function thread_init(thread_id)
    -- 在这里编写线程初始化的逻辑，如创建线程级别的连接，设置线程参数等
end

-- 线程执行完成后的清理工作
function thread_done(thread_id)
    -- 在这里编写线程结束后的清理逻辑，如关闭线程级别的连接，释放线程资源等
end

-- 在测试中执行的具体操作，如查询、插入等
function event(thread_id)
    -- 在这里编写具体的数据库操作代码，如查询、插入等
    -- 可以使用数据库连接池中的连接对象执行操作
end
