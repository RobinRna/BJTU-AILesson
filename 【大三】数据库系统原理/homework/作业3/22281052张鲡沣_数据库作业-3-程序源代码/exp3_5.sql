-- 单表查询 + 多表连接查询 SQL 语句设计

/*单表查询*/
-- 查询all乘客信息
SELECT * FROM Passenger;

-- 查询所有已经支付的订单
SELECT * FROM Orderinfo WHERE payment=1;

-- 查询CA1234票务信息
SELECT id_card, gate, boarding_time FROM Ticket WHERE flight_number='MU4241';

/*多表连接查询*/
-- 查询所有乘客及其所订的航班号、舱位信息
SELECT p.passname, t.flight_number, t.cabin_seat
FROM Passenger p, Ticket t
WHERE p.id_card=t.id_card;


-- 查询乘客姓名、订单金额
SELECT p.passname, o.moneys
FROM Passenger p, Orderinfo o
WHERE p.id_card = o.id_card;

-- 查询每个航班的售出票数，筛选出票数大于5的航班
SELECT t.flight_number, COUNT(*) as cnt
FROM Ticket t, Flight f
WHERE t.flight_number = f.flight_number
GROUP BY t.flight_number
HAVING COUNT(*)>5;

-- 查询订购了航班 CA1234 的所有乘客的姓名
SELECT passname
FROM Passenger
WHERE id_card IN (
    SELECT id_card
    FROM Ticket
    WHERE flight_number = 'CA1234'
);

-- 找出没有订过机票的乘客所有信息
SELECT *
FROM Passenger p
WHERE NOT EXISTS(
    SELECT *
    FROM Ticket t
    WHERE t.id_card = p.id_card
);