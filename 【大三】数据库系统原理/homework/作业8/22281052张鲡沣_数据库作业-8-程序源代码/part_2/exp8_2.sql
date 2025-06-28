-- 每个窗口运行！
SET autocommit = 0;

-- 在 airlinedb 数据库中创建测试表（模拟账户余额）
USE airlinedb;

DROP TABLE IF EXISTS TestBalance;
CREATE TABLE TestBalance (
    id INT PRIMARY KEY,
    account_name VARCHAR(50),
    balance DECIMAL(10, 2)
);

-- 插入初始数据
INSERT INTO TestBalance (id, account_name, balance) VALUES (1, 'Alice', 1000.00);
INSERT INTO TestBalance (id, account_name, balance) VALUES (2, 'Bob', 500.00);
COMMIT; -- 提交初始数据插入