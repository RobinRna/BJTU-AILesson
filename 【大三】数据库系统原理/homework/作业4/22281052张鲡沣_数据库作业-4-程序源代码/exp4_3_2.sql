/*
viewer：只读权限
ticket_editor：只可以编辑订单、机票
admin_flight：可以操作航班相关表
*/

-- ==================================================================
-- 4. 创建角色，并把角色授予用户或收回用户的某个角色
-- ==================================================================
DROP ROLE IF EXISTS 'viewer'@'localhost';
DROP ROLE IF EXISTS 'ticket_editor'@'localhost';
DROP ROLE IF EXISTS 'admin_flight'@'localhost';

-- 创建角色
CREATE ROLE 'viewer'@'localhost';
CREATE ROLE 'ticket_editor'@'localhost';
CREATE ROLE 'admin_flight'@'localhost';

-- viewer: 只读
GRANT SELECT ON airlinedb.Airport TO 'viewer'@'localhost';
GRANT SELECT ON airlinedb.Airline TO 'viewer'@'localhost';
GRANT SELECT ON airlinedb.Flight TO 'viewer'@'localhost';
GRANT SELECT ON airlinedb.Passenger TO 'viewer'@'localhost';
GRANT SELECT ON airlinedb.Ticket TO 'viewer'@'localhost';
GRANT SELECT ON airlinedb.Orderinfo TO 'viewer'@'localhost';
GRANT SELECT ON airlinedb.Flightsum TO 'viewer'@'localhost';
GRANT SELECT ON airlinedb.Passhistoryfli TO 'viewer'@'localhost';
GRANT SELECT ON airlinedb.Passfeturefli TO 'viewer'@'localhost';
GRANT SELECT ON airlinedb.UserInfo TO 'viewer'@'localhost';
GRANT SELECT ON airlinedb.FlightTime TO 'viewer'@'localhost';
GRANT SELECT ON airlinedb.Airlineflicount TO 'viewer'@'localhost';

-- ticket_editor: 编辑订单、机票
GRANT SELECT, INSERT, UPDATE, DELETE ON airlinedb.Ticket TO 'ticket_editor'@'localhost';
GRANT SELECT, INSERT, UPDATE, DELETE ON airlinedb.Orderinfo TO 'ticket_editor'@'localhost';
GRANT SELECT ON airlinedb.Flight TO 'ticket_editor'@'localhost';
GRANT SELECT ON airlinedb.Passenger TO 'ticket_editor'@'localhost';
GRANT SELECT ON airlinedb.Airport TO 'ticket_editor'@'localhost';
GRANT SELECT ON airlinedb.Airline TO 'ticket_editor'@'localhost';

-- admin_flight: 操作航班相关表
GRANT SELECT, INSERT, UPDATE, DELETE ON airlinedb.Flight TO 'admin_flight'@'localhost';
GRANT SELECT ON airlinedb.Airport TO 'admin_flight'@'localhost';
GRANT SELECT ON airlinedb.Airline TO 'admin_flight'@'localhost';

-- 将角色授予用户 
-- 清理之前直接授予用户的权限
DROP USER IF EXISTS 'alice'@'localhost';
DROP USER IF EXISTS 'bob'@'localhost';
DROP USER IF EXISTS 'robin'@'localhost';
CREATE USER 'alice'@'localhost' IDENTIFIED BY '12345678';
CREATE USER 'bob'@'localhost' IDENTIFIED BY '12345678';
CREATE USER 'robin'@'localhost' IDENTIFIED BY '12345678';

-- 将 viewer 角色授予 alice
GRANT 'viewer'@'localhost' TO 'alice'@'localhost';
-- 将 ticket_editor 角色授予 bob
GRANT 'ticket_editor'@'localhost' TO 'bob'@'localhost';
-- 将 admin_flight 角色授予 robin
GRANT 'admin_flight'@'localhost' TO 'robin'@'localhost';
-- 同时将 viewer 角色也授予 robin (一个用户可以有多个角色)
GRANT 'viewer'@'localhost' TO 'robin'@'localhost';

-- 查看用户的权限，现在应该包含角色的权限
SHOW GRANTS FOR 'alice'@'localhost';
SHOW GRANTS FOR 'bob'@'localhost';
SHOW GRANTS FOR 'robin'@'localhost';

-- 从用户收回角色
-- 从 robin 收回 viewer 角色
REVOKE 'viewer'@'localhost' FROM 'robin'@'localhost';
-- 查看 'robin' 的权限
SHOW GRANTS FOR 'robin'@'localhost';

