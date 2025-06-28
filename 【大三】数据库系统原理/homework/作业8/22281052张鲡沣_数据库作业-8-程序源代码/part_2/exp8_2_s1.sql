-- SET SESSION TRANSACTION ISOLATION LEVEL <level>;：设置当前会话的事务隔离级别。
-- START TRANSACTION; 或 BEGIN;：开始一个新事务。
-- COMMIT;：提交事务，使所有更改永久生效。
-- ROLLBACK;：回滚事务，撤销所有未提交的更改。
-- SELECT @@session.transaction_isolation;：查看当前会话的隔离级别。



-- 场景一：脏读 (Dirty Read) 演示
USE airlinedb;
UPDATE TestBalance SET balance = 1000.00 WHERE id = 1;
COMMIT;
SELECT * FROM TestBalance WHERE id = 1; -- 确认 Alice 余额为 1000.00

-- 1. 设置隔离级别为 READ UNCOMMITTED，并开始事务
SET SESSION TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
START TRANSACTION;

-- 2. 修改 Alice 的余额，但不提交 (模拟转账扣款，但未完成)
UPDATE TestBalance SET balance = balance - 200 WHERE id = 1; -- Alice 余额变为 800.00
SELECT * FROM TestBalance WHERE id = 1; -- 在会话1中看到 800.00

-- ***请暂停，转到会话2执行下一步***

-- 3. 回滚事务 (模拟转账失败被撤销)
ROLLBACK; -- Alice 的余额恢复为 1000.00
SELECT * FROM TestBalance WHERE id = 1; -- 在会话1中看到 1000.00

-- ***请暂停，转到会话2执行下一步***

-- 其他隔离级
-- 1. 设置隔离级别为 READ COMMITTED (或 REPEATABLE READ / SERIALIZABLE)，并开始事务
SET SESSION TRANSACTION ISOLATION LEVEL REPEATABLE READ ; 
START TRANSACTION;

-- 2. 修改 Alice 的余额，但不提交
UPDATE TestBalance SET balance = balance - 200 WHERE id = 1; -- Alice 余额变为 800.00
SELECT * FROM TestBalance WHERE id = 1; -- 在会话1中看到 800.00

-- ***请暂停，转到会话2执行下一步***

-- 3. 提交事务
COMMIT; -- Alice 的余额变为 800.00

-- ***请暂停，转到会话2执行下一步***







-- 场景二：不可重复读 (Non-repeatable Read) 演示
USE airlinedb;
UPDATE TestBalance SET balance = 1000.00 WHERE id = 1;
COMMIT;
SELECT * FROM TestBalance WHERE id = 1; -- 确认 Alice 余额为 1000.00

-- 1. 设置隔离级别为 READ COMMITTED，并开始事务
SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;
START TRANSACTION;

-- 2. 第一次读取 Alice 的余额
SELECT * FROM TestBalance WHERE id = 1;
-- 预期结果：balance 显示 1000.00

-- ***请暂停，转到会话2执行下一步***

-- 3. 在同一事务中再次读取 Alice 的余额
SELECT * FROM TestBalance WHERE id = 1;
-- 预期结果：balance 显示 900.00 (与第一次读取的值 1000.00 不同)
COMMIT;



-- 场景三：丢失修改 (Lost Update) 演示
USE airlinedb;
UPDATE TestBalance SET balance = 1000.00 WHERE id = 1;
COMMIT;
SELECT * FROM TestBalance WHERE id = 1; -- 确认 Alice 余额为 1000.00

-- 1. 设置隔离级别并开始事务
SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;
START TRANSACTION;

-- 2. 读取 Alice 的余额到本地变量 (模拟应用程序读取数据到内存进行处理)
SELECT balance INTO @balance_s1 FROM TestBalance WHERE id = 1;
SELECT @balance_s1; -- 预期 1000.00
-- 等待会话2读取...

-- 3. 基于读取到的值进行修改 (减少 100)
UPDATE TestBalance SET balance = @balance_s1 - 100 WHERE id = 1; -- 数据库中 Alice 余额变为 900.00
COMMIT;
SELECT * FROM TestBalance WHERE id = 1; -- 确认 900.00
-- 等待会话2修改...