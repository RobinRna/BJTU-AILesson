-- 导入方式：
-- DELIMITER //
-- \. D:\Learning_ComputerLanguages\learning_language_sql\1_Database\4_exp7\part_1\exp7_3_2.sql
-- DELIMITER ;


-- 触发器1：AFTER INSERT ON Passenger，在 Passenger 表成功插入新记录后触发
CREATE TRIGGER after_passenger_insert
AFTER INSERT ON Passenger
FOR EACH ROW -- 对于每一行受影响的记录都执行一次触发器体
BEGIN
    -- NEW 伪行（pseudo-row）包含了新插入的记录的数据
    INSERT INTO TriggerLog (table_name, operation, item_id, description)
    VALUES (
        'Passenger',
        'INSERT',
        NEW.id_card, -- 新记录的身份证号作为项目ID
        CONCAT('New passenger inserted. ID: ', NEW.id_card, ', Name: ', NEW.passname, ', Age: ', NEW.age)
    );
END // 


-- 触发器2：AFTER UPDATE ON Passenger，在 Passenger 表成功更新记录后触发
CREATE TRIGGER after_passenger_update
AFTER UPDATE ON Passenger
FOR EACH ROW
BEGIN
    -- OLD 伪行包含更新前的记录数据，NEW 伪行包含更新后的记录数据
    INSERT INTO TriggerLog (table_name, operation, item_id, description)
    VALUES (
        'Passenger',
        'UPDATE',
        NEW.id_card, -- 更新后记录的身份证号作为项目ID
        CONCAT('Passenger updated. ID: ', OLD.id_card, '. Name from "', OLD.passname, '" updated to "', NEW.passname, '". Phone from "', OLD.phone, '" updated to "', NEW.phone, '"')
    );
END // 


-- 触发器3：AFTER DELETE ON Passenger，在 Passenger 表成功删除记录后触发
CREATE TRIGGER after_passenger_delete
AFTER DELETE ON Passenger
FOR EACH ROW
BEGIN
    -- OLD 伪行包含了被删除的记录的数据
    INSERT INTO TriggerLog (table_name, operation, item_id, description)
    VALUES (
        'Passenger', 
        'DELETE',
        OLD.id_card, -- 被删除记录的身份证号作为项目ID
        CONCAT('Passenger deleted. ID: ', OLD.id_card, ', Name: ', OLD.passname)
    );
END //
