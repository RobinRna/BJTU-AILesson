-- 备份单个表

mysqldump -u root -p airlinedb Passenger > passenger_backup.sql

-- -u root: 指定用户名为 root。
-- -p: 提示输入密码（输入命令后会要求输入密码）。
-- airlinedb: 指定要备份的数据库。
-- Passenger: 指定要备份的表名。
-- >: 将输出重定向到文件。
-- passenger_backup.sql: 备份文件的名称。

-- 备份整个数据库
mysqldump -u root -p airlinedb > airlinedb_full_backup.sql