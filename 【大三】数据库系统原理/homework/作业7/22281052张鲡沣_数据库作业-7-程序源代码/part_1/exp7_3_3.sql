-- 测试 INSERT 触发器

-- 插入一条新的乘客记录到 Passenger 表
INSERT INTO Passenger (id_card, passname, age, phone)
VALUES ('51010119950101123X', 'Wangping', 28, '13912345678');

-- 查询 TriggerLog 表，查看是否生成了对应的日志记录
SELECT * FROM TriggerLog WHERE table_name = 'Passenger' AND operation = 'INSERT' ORDER BY log_time DESC LIMIT 5;


-- 测试 UPDATE 触发器
UPDATE Passenger
SET phone = '13887654321', age = 29
WHERE id_card = '51010119950101123X';

-- 查询 TriggerLog 表，查看是否生成了对应的日志记录
SELECT * FROM TriggerLog WHERE table_name = 'Passenger' AND operation = 'UPDATE' ORDER BY log_time DESC LIMIT 5;

-- 测试 DELETE 触发器
-- 删除该乘客记录
-- **重要提示：** 如果该乘客在 Ticket 或 Orderinfo 表中有关联记录，并且 Passenger 表的外键没有设置 ON DELETE CASCADE，这里的 DELETE 操作会失败，并且 after_passenger_delete 触发器也不会被触发执行。
-- 为了成功测试删除触发器，请确保要删除的乘客 ID 没有关联的 Ticket 或 Orderinfo 记录，或者先手动删除这些关联记录，或者在数据库中修改外键约束属性。
DELETE FROM Passenger
WHERE id_card = '51010119950101123X';

-- 查询 TriggerLog 表，查看是否生成了对应的日志记录
SELECT * FROM TriggerLog WHERE table_name = 'Passenger' AND operation = 'DELETE' ORDER BY log_time DESC LIMIT 5;