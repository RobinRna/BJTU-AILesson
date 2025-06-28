/*通过视图进行数据查询*/
-- 查询所有航班的简要信息
SELECT *
FROM Flightsum
WHERE departure_airport_name = 'PEK'
   OR arrival_airport_name = 'PEK';

-- 查询某乘客的历史航班信息
SELECT * FROM Passhistoryfli WHERE id_card = '110101199001011234';

-- 查询某乘客的未来航班信息
SELECT * FROM Passfeturefli WHERE id_card = '110101199001011234';

-- 查询用户个人信息
SELECT * FROM UserInfo WHERE id_card = '110101199001011234';

-- 查询某航班的飞行时间
SELECT * FROM FlightTime WHERE flight_number = 'CA1234';

-- 查询每个航空公司航班数量
SELECT * FROM Airlineflicount;

/*尝试对视图进行修改或删除*/
-- 尝试更新可修改的 UserInfo 视图（成功）
UPDATE UserInfo
SET phone = '19988887777'
WHERE id_card = '110101199001011234';

-- 尝试从历史航班视图删除记录（失败）
DELETE FROM Passhistoryfli WHERE id_card = '110101199001011234';

-- 尝试修改 FlightTime 视图中的计算字段（失败）
UPDATE FlightTime
SET flight_time = 999
WHERE flight_number = 'CA1234';

-- 尝试删除 Airlineflicount 分组视图中的记录（失败）
DELETE FROM Airlineflicount WHERE airline_code = 'ZH';
