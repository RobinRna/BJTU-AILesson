-- 导入方式：
-- DELIMITER //
-- \. D:\Learning_ComputerLanguages\learning_language_sql\1_Database\4_exp7\part_1\exp7_1.sql
-- DELIMITER ;

-- 对于JDBC的扩充
-- 插入乘客：AddPassenger
DROP PROCEDURE IF EXISTS AddPassenger;
CREATE PROCEDURE AddPassenger(
    IN in_id_card VARCHAR(20),
    IN in_passname VARCHAR(50),
    IN in_age INT,
    IN in_phone VARCHAR(100)
)
BEGIN
    INSERT INTO Passenger (id_card, passname, age, phone)
    VALUES (in_id_card, in_passname, in_age, in_phone);
END //

-- 修改乘客电话：UpdatePassengerPhone
DROP PROCEDURE IF EXISTS UpdatePassengerPhone;
CREATE PROCEDURE UpdatePassengerPhone(
    IN in_id_card VARCHAR(20),
    IN in_phone VARCHAR(100)
)
BEGIN
    UPDATE Passenger
    SET phone = in_phone
    WHERE id_card = in_id_card;
END //

-- 删除乘客：DeletePassenger
DROP PROCEDURE IF EXISTS DeletePassenger;
CREATE PROCEDURE DeletePassenger(
    IN in_id_card VARCHAR(20)
)
BEGIN
    DELETE FROM Passenger
    WHERE id_card = in_id_card;
END //

-- 查询航班：GetFlightsByRoute
DROP PROCEDURE IF EXISTS GetFlightsByRoute;
CREATE PROCEDURE GetFlightsByRoute(
    IN dep_airport VARCHAR(10),
    IN arr_airport VARCHAR(10)
)
BEGIN
    SELECT
        f.flight_number,
        f.air_model,
        f.departure_time,
        f.arrival_time,
        a1.airport_name AS departure_airport_name,
        a1.city AS departure_city,
        a2.airport_name AS arrival_airport_name,
        a2.city AS arrival_city,
        al.airline_name
    FROM Flight f
    JOIN Airport a1 ON f.departure_airport = a1.airport_code
    JOIN Airport a2 ON f.arrival_airport = a2.airport_code
    JOIN Airline al ON f.airline_code = al.airline_code
    WHERE f.departure_airport = dep_airport
      AND f.arrival_airport = arr_airport;
END //