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
CREATE Table Passenger (
    id_card VARCHAR(20) PRIMARY KEY,
    passname VARCHAR(50) NOT NULL,
    age INT NOT NULL CHECK (
        age >= 0
        AND age < 120
    ),
    phone VARCHAR(100)
);
-- 机票表
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
CREATE Table Orderinfo (
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    id_card VARCHAR(20) NOT NULL,
    moneys DECIMAL(10, 2) NOT NULL,
    payment INT NOT NULL CHECK (payment in (0, 1)),
    Foreign Key (id_card) REFERENCES Passenger (id_card)
);