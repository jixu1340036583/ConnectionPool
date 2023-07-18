local sysbench = require("sysbench")

-- 初始化函数，用于设置测试参数
function sysbench.cmdline.commands.prepare()
   -- 设置线程数
   sysbench.opt.threads = 10
   -- 设置测试时长
   sysbench.opt.duration = 10
   -- 设置测试类型为自定义Lua脚本
   sysbench.cmdline.options["test"] = {value = "test.lua"}
end

-- 测试过程中的主要操作
function sysbench.cmdline.commands.run()
   -- 从C++实现的数据库连接池获取连接
   local connection = get_db_connection()
   -- 执行查询，例如SELECT语句
   local result = execute_query(connection, "insert into User(name,password,state) values('test','zxc','offline')")
end

-- sysbench db_connection_pool_test.lua prepare
-- sysbench db_connection_pool_test.lua run