-- ==================================================================
-- 1. 创建用户
-- ==================================================================
DROP USER IF EXISTS 'alice'@'localhost';
DROP USER IF EXISTS 'bob'@'localhost';
DROP USER IF EXISTS 'robin'@'localhost';

-- 创建用户，设置密码
CREATE USER 'alice'@'localhost' IDENTIFIED BY '12345678';
CREATE USER 'bob'@'localhost' IDENTIFIED BY '12345678';
CREATE USER 'robin'@'localhost' IDENTIFIED BY '12345678';

-- 显示已创建的用户
SELECT user, host FROM mysql.user WHERE user IN ('alice', 'bob', 'robin');

-- 授予 数据库级的 USAGE 权限，可以进入数据库
GRANT USAGE ON airlinedb.* TO 'alice'@'localhost';
GRANT USAGE ON airlinedb.* TO 'alice'@'localhost';
GRANT USAGE ON airlinedb.* TO 'alice'@'localhost';
-- ==================================================================
-- 2. 为不同的用户授予和收回表级权限
-- ==================================================================

-- 为用户alice操作 
-- 授予表级 SELECT 权限
GRANT SELECT ON airlinedb.Airport TO 'alice'@'localhost';
-- 授予表级 INSERT 权限
GRANT INSERT ON airlinedb.Passenger TO 'alice'@'localhost';
-- 查看 alice 的当前权限
SHOW GRANTS FOR 'alice'@'localhost';

-- 撤销 alice 对 Passenger 表的 INSERT 权限
REVOKE INSERT ON airlinedb.Passenger FROM 'alice'@'localhost';
-- 查看 'alice' 的权限
SHOW GRANTS FOR 'alice'@'localhost';


-- 为用户 bob 操作 
-- 授予对 Ticket 表的所有基本权限
GRANT SELECT, INSERT, UPDATE, DELETE ON airlinedb.Ticket TO 'bob'@'localhost';
-- 查看 bob 的当前权限
SHOW GRANTS FOR 'bob'@'localhost';

-- 撤销 bob 对 Ticket 表的 DELETE 权限
REVOKE DELETE ON airlinedb.Ticket FROM 'bob'@'localhost';
-- 查看 bob 的权限
SHOW GRANTS FOR 'bob'@'localhost';

-- 为用户 robin 操作 
-- 授予对 Flight 表的 ALL PRIVILEGES
GRANT ALL PRIVILEGES ON airlinedb.Flight TO 'robin'@'localhost';
-- 查看 robin 的权限
SHOW GRANTS FOR 'robin'@'localhost';

-- 撤销 robin 对 Flight 表的 UPDATE 权限
REVOKE UPDATE ON airlinedb.Flight FROM 'robin'@'localhost';
-- 查看 robin 的权限
SHOW GRANTS FOR 'robin'@'localhost';

-- ==================================================================
-- 3. 为不同的用户授予和收回属性列级的权限
-- ==================================================================

-- 为用户 alice 操作
-- 授予 alice 对 Passenger 表的 'passname' 和 'phone' 列的 SELECT 权限
GRANT SELECT (passname, phone) ON airlinedb.Passenger TO 'alice'@'localhost';
-- 授予 alice 对 Passenger 表的 'phone' 列的 UPDATE 权限
GRANT UPDATE (phone) ON airlinedb.Passenger TO 'alice'@'localhost';
-- 查看 alice 的权限
SHOW GRANTS FOR 'alice'@'localhost';


-- 撤销 alice 权限
REVOKE SELECT (passname) ON airlinedb.Passenger FROM 'alice'@'localhost';
-- 查看 alice 的权限，验证撤销
SHOW GRANTS FOR 'alice'@'localhost';
