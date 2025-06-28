DELIMITER //

CREATE PROCEDURE insert_test_data(IN total_rows INT)
BEGIN
    DECLARE i INT DEFAULT 1;
    DECLARE id_prefix VARCHAR(10) DEFAULT 'ID';
    DECLARE base_card BIGINT DEFAULT 10000000;
    DECLARE seat_list JSON;
    SET seat_list = JSON_ARRAY("12A", "14C", "15B", "19D", "20E");

    WHILE i <= total_rows DO
        SET @id_card = CONCAT(id_prefix, base_card + i);
        SET @name = CONCAT('User', i);
        SET @age = FLOOR(RAND() * 50) + 18;
        SET @phone = CONCAT('13', LPAD(FLOOR(RAND()*100000000), 8, '0'));

        INSERT INTO Passenger (id_card, passname, age, phone)
        VALUES (@id_card, @name, @age, @phone);

        SET @flight_number = IF(RAND() > 0.5, 'CA1234', 'MU5678');
        SET @seat = JSON_UNQUOTE(JSON_EXTRACT(seat_list, CONCAT('$[', FLOOR(RAND()*5), ']')));
        SET @gate = CONCAT(CHAR(FLOOR(RAND()*4)+65), LPAD(FLOOR(RAND()*10), 2, '0'));
        SET @boarding_time = NOW();

        INSERT INTO Ticket (flight_number, id_card, seat_number, gate, boarding_time, cabin_seat)
        VALUES (@flight_number, @id_card, @seat, @gate, @boarding_time, IF(RAND() > 0.7, 'C', 'Y'));

        INSERT INTO Orderinfo (id_card, moneys, payment)
        VALUES (@id_card, ROUND(RAND() * 1000 + 500, 2), FLOOR(RAND()*2));

        SET i = i + 1;
    END WHILE;
END //

DELIMITER ;


-- 插入 100000 条数据
CALL insert_test_data(100000);

