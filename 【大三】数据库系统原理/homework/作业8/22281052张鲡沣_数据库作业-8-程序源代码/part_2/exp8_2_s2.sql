-- SET SESSION TRANSACTION ISOLATION LEVEL <level>;：设置当前会话的事务隔离级别。
-- START TRANSACTION; 或 BEGIN;：开始一个新事务。
-- COMMIT;：提交事务，使所有更改永久生效。
-- ROLLBACK;：回滚事务，撤销所有未提交的更改。
-- SELECT @@session.transaction_isolation;：查看当前会话的隔离级别。



-- 场景一：脏读 (Dirty Read) 演示

-- 1. 设置隔离级别为 READ UNCOMMITTED，并开始事务
SET SESSION TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
START TRANSACTION;

-- 2. 读取 Alice 的余额 (此时会话1未提交)
SELECT * FROM TestBalance WHERE id = 1;
-- 预期结果：balance 显示 800.00 (脏读发生)

-- ***请暂停，转到会话1执行下一步***

-- 3. 再次读取 Alice 的余额 (此时会话1已回滚)
SELECT * FROM TestBalance WHERE id = 1;
-- 预期结果：balance 显示 1000.00。
-- 此时会话2第一次读到的 800.00 就是“脏数据”，因为它被回滚了，从未真正存在于数据库的最终状态中。
COMMIT;


-- 更改隔离级别
-- 1. 设置隔离级别为 READ COMMITTED (或 REPEATABLE READ / SERIALIZABLE)，并开始事务
SET SESSION TRANSACTION ISOLATION LEVEL REPEATABLE READ;
START TRANSACTION;

-- 2. 读取 Alice 的余额 (此时会话1未提交)
SELECT * FROM TestBalance WHERE id = 1;
-- 预期结果：balance 依然显示 1000.00。会话2只会看到已提交的数据，未提交的修改被阻止。

-- ***请暂停，转到会话1执行下一步***

-- 3. 再次读取 Alice 的余额 (此时会话1已提交)
SELECT * FROM TestBalance WHERE id = 1;
-- 预期结果：balance 显示 800.00。会话2现在看到会话1提交后的数据。
COMMIT;











-- 场景二：不可重复读 (Non-repeatable Read) 演示
-- 1. 设置隔离级别为 READ COMMITTED，并开始事务
SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;
START TRANSACTION;

-- 2. 修改 Alice 的余额并提交
UPDATE TestBalance SET balance = balance - 100 WHERE id = 1; -- Alice 余额变为 900.00
COMMIT; -- 提交修改
SELECT * FROM TestBalance WHERE id = 1; -- 确认 900.00

-- ***请暂停，转到会话1执行下一步***



-- 场景三：丢失修改 (Lost Update) 演示
USE airlinedb;
UPDATE TestBalance SET balance = 1000.00 WHERE id = 1;
COMMIT;
SELECT * FROM TestBalance WHERE id = 1; -- 确认 Alice 余额为 1000.00

-- 1. 设置隔离级别并开始事务
SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;
START TRANSACTION;

-- 2. 读取 Alice 的余额到本地变量
SELECT balance INTO @balance_s2 FROM TestBalance WHERE id = 1;
SELECT @balance_s2; -- 预期 1000.00
-- 等待会话1修改...

-- 3. 基于读取到的值进行修改 (减少 200)
UPDATE TestBalance SET balance = @balance_s2 - 200 WHERE id = 1; -- 数据库中 Alice 余额变为 800.00 (基于 @balance_s2=1000)
COMMIT;
SELECT * FROM TestBalance WHERE id = 1; -- 确认 800.00