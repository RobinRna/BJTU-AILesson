USE airlinedb;

-- 创建用于记录触发器事件的日志表
CREATE TABLE TriggerLog (
    log_id INT AUTO_INCREMENT PRIMARY KEY,    -- 日志记录的唯一标识
    table_name VARCHAR(50) NOT NULL,          -- 发生变动的表名
    operation VARCHAR(10) NOT NULL,           -- 变动类型 (如 'INSERT', 'UPDATE', 'DELETE')
    item_id VARCHAR(50),                      -- 发生变动的记录的主键或其他标识（此处记录乘客身份证号）
    description TEXT,                         -- 对变动的简要描述（可以包含旧值和新值）
    log_time DATETIME DEFAULT CURRENT_TIMESTAMP -- 变动发生的精确时间，默认为当前时间戳
);

