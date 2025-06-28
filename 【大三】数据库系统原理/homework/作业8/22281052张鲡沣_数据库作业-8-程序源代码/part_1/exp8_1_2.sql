-- 确认 Binlog 是否已经开启
SHOW VARIABLES LIKE 'log_bin';
SHOW VARIABLES LIKE 'binlog_format';
SHOW VARIABLES LIKE 'datadir';

-- 查看当前的 Binlog 文件，确定 Binlog 文件名及其写入位置
SHOW BINARY LOG STATUS;

-- 执行数据修改操作
USE airlinedb;

-- 插入一条新的乘客记录
INSERT INTO Passenger (id_card, passname, age, phone)
VALUES ('510101200001019000', '测试用户Binlog', 35, '13900001234');

-- 更新乘客的电话号码
UPDATE Passenger
SET phone = '13800000001'
WHERE id_card = '110101199001011234';

-- 记录操作后的 Binlog 位置
SHOW BINARY LOG STATUS;

-- 之后打开命令行终端进行操作 exp8_2.sh
