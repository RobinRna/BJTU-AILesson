-- 创建数据库
CREATE DATABASE airlinedb;
USE airlinedb;
-- 机场表
CREATE TABLE Airport (
    airport_code VARCHAR(10) PRIMARY KEY,
    airport_name VARCHAR(100) NOT NULL,
    city VARCHAR(50) NOT NULL,
    flight_zone VARCHAR(10) NOT NULL
);
-- 航空公司表
CREATE Table Airline (
    airline_code VARCHAR(10) PRIMARY KEY,
    airline_name VARCHAR(100) NOT NULL,
    contact_info VARCHAR(100)
);
-- 航班表
CREATE Table Flight (
    flight_number VARCHAR(20) PRIMARY KEY,
    air_model VARCHAR(50) NOT NULL,
    departure_time DATETIME NOT NULL,
    arrival_time DATETIME NOT NULL,
    departure_airport VARCHAR(10) NOT NULL,
    arrival_airport VARCHAR(10) NOT NULL,
    airline_code VARCHAR(10) NOT NULL,
    Foreign Key (departure_airport) REFERENCES Airport (airport_code),
    Foreign Key (arrival_airport) REFERENCES Airport (airport_code),
    Foreign Key (airline_code) REFERENCES Airline (airline_code)
);
-- 乘客表
CREATE TABLE Passenger (
    id_card VARCHAR(20) PRIMARY KEY,
    passname VARCHAR(50) NOT NULL,
    age INT NOT NULL,
    phone VARCHAR(100),
    CONSTRAINT chk_age CHECK (age >= 0 AND age < 120)  -- 命名约束
);

-- 机票表 AUTO_INCREMENT 
CREATE Table Ticket (
    ticket_id INT AUTO_INCREMENT PRIMARY KEY,
    flight_number VARCHAR(20) NOT NULL,
    id_card VARCHAR(20) NOT NULL,
    seat_number VARCHAR(10) NOT NULL,
    gate VARCHAR(10),
    boarding_time DATETIME NOT NULL,
    cabin_seat VARCHAR(10),
    Foreign Key (flight_number) REFERENCES Flight (flight_number),
    Foreign Key (id_card) REFERENCES Passenger (id_card)
);
-- 订单表 
CREATE TABLE Orderinfo (
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    id_card VARCHAR(20) NOT NULL,
    moneys DECIMAL(10, 2) NOT NULL,
    payment INT NOT NULL,
    CONSTRAINT chk_payment CHECK (payment IN (0, 1)),
    FOREIGN KEY (id_card) REFERENCES Passenger(id_card)
);

-- 航班信息查询 行列子集视图
CREATE VIEW Flightsum AS
SELECT flight_number, departure_time, arrival_time,
    (
        SELECT airport_code
        FROM Airport
        WHERE Airport.airport_code = Flight.departure_airport
    ) AS departure_airport_name,
    (
        SELECT city
        FROM Airport
        WHERE Airport.airport_code = Flight.departure_airport
    ) AS departure_city,
    (
        SELECT airport_code
        FROM Airport
        WHERE Airport.airport_code = Flight.arrival_airport
    ) AS arrival_airport_name,
    (
        SELECT city
        FROM Airport
        WHERE Airport.airport_code = Flight.arrival_airport
    ) AS arrival_city
FROM Flight;


-- 用户历史航班记录 行列子集视图
CREATE VIEW Passhistoryfli AS
SELECT id_card, passname,
    (
        SELECT flight_number
        FROM Ticket
        WHERE Ticket.id_card = Passenger.id_card
    ) AS flight_number,
    (
        SELECT departure_time
        FROM Flight
        WHERE Flight.flight_number = (
                SELECT flight_number
                FROM Ticket
                WHERE Ticket.id_card = Passenger.id_card
            )
            AND departure_time <= NOW()
    ) AS departure_time,
    (
        SELECT arrival_time
        FROM Flight
        WHERE Flight.flight_number = (
                SELECT flight_number
                FROM Ticket
                WHERE Ticket.id_card = Passenger.id_card
            )
            AND departure_time <= NOW()
    ) AS arrival_time
FROM Passenger;

-- 用户未来航班信息 行列子集视图
CREATE VIEW Passfeturefli AS
SELECT
    id_card,
    passname,
    (
        SELECT flight_number
        FROM Ticket
        WHERE
            Ticket.id_card = Passenger.id_card
    ) AS flight_number,
    (
        SELECT departure_time
        FROM Flight
        WHERE
            Flight.flight_number = (
                SELECT flight_number
                FROM Ticket
                WHERE
                    Ticket.id_card = Passenger.id_card
            )
            AND departure_time > NOW()
    ) AS departure_time,
    (
        SELECT arrival_time
        FROM Flight
        WHERE
            Flight.flight_number = (
                SELECT flight_number
                FROM Ticket
                WHERE
                    Ticket.id_card = Passenger.id_card
            )
            AND departure_time > NOW()
    ) AS arrival_time,
    (
        SELECT airline_name
        FROM Airline
        WHERE
            Airline.airline_code = (
                SELECT airline_code
                FROM Flight
                WHERE
                    Flight.flight_number = (
                        SELECT flight_number
                        FROM Ticket
                        WHERE
                            Ticket.id_card = Passenger.id_card
                    )
            )
    ) AS airline_name
FROM Passenger;


-- 个人信息视图 行列子集视图
CREATE VIEW UserInfo AS
SELECT id_card, passname, age, phone
FROM Passenger;


-- 航班的飞行时长 带表达式的视图
CREATE VIEW FlightTime AS 
SELECT flight_number, departure_time, arrival_time,
    TIMESTAMPDIFF(MINUTE, departure_time, arrival_time) AS flight_time
FROM Flight;

-- 航空公司下航班数量 分组视图
CREATE VIEW Airlineflicount AS
SELECT airline_code, COUNT(*) AS flight_count
FROM Flight
GROUP BY airline_code;


