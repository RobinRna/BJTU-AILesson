-- 索引

/*唯一索引*/
-- 创建唯一索引：手机号不重复
CREATE UNIQUE INDEX id_passphone ON Passenger(phone);

-- 创建唯一索引：同一航班一个座位只能安排给一个人
CREATE UNIQUE INDEX id_ticseat ON Ticket(flight_number, seat_number);

/*聚集索引*/
-- 在MySQL用不了
-- CREATE CLUSTERED INDEX idx_passenger_id ON Passenger(id_card);