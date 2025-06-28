-- 完整性测试语句

/*实体完整性*/
-- 插入一个新机场
-- 预期结果插入正常
INSERT INTO Airport VALUES ('CAN', 'Guangzhou Baiyun International Airport', 'Guangzhou', '4F');

-- 尝试插入与已有主键重复的机场
-- 预期结果 ERROR 1062 (23000): Duplicate entry 'PEK' for key 'PRIMARY'
INSERT INTO Airport VALUES ('PEK', 'Some Airport', 'AnyCity', '4F');

/*参照完整性*/
-- 以 CA、PEK、PVG 为外键的航班
-- 预期结果插入正常
INSERT INTO Flight VALUES ('CA9999', 'AirbusA330', '2024-04-12 10:00:00', '2024-04-12 13:00:00', 'PEK', 'PVG', 'CA');

-- 插入航班，airline_code 不存在
-- 预期结果 ERROR 1452 (23000): Cannot add or update a child row: a foreign key constraint fails
INSERT INTO Flight VALUES ('AB1234', 'Boeing777', '2024-05-01 10:00:00', '2024-05-01 12:00:00', 'PEK', 'PVG', 'AB');

/*用户定义完整性*/
-- 合法年龄
-- 预期结果插入正常
INSERT INTO Passenger VALUES ('110101199003035678', 'Wangwu', 25, '13700000000');
-- 合法支付状态
-- 预期结果插入正常
INSERT INTO Orderinfo (id_card, moneys, payment) VALUES ('110101199003035678', 999.99, 1);

-- 非法支付状态（只能是0或1）
-- 预期结果 Check constraint 'Orderinfo_chk_1' is violated
INSERT INTO Orderinfo (id_card, moneys, payment) VALUES ('110101199001011234', 88.88, 2);
-- 非法年龄（超过上限）
-- 预期结果 Check constraint 'Passenger_chk_1' is violated
INSERT INTO Passenger VALUES ('110101199004046789', 'Zhaoliu', 150, '13600000000');