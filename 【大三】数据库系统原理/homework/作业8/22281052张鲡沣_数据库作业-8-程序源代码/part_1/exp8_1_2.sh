# 进入 MySQL binlog 工具所在的目录
cd /d S:
cd "S:/MySQL/MySQL Server 9.0/bin" # 替换为您的实际安装路径

# 假设您在 SHOW MASTER STATUS 中看到的 Binlog 文件是 ROBIN-bin.000001，操作后位置是 1500
# 使用 --stop-position 查找操作结束位置
mysqlbinlog --database=airlinedb --stop-position=1500 "S:/MySQL/Data/MySQL Server 9.0/Data/ROBIN-bin.000023"

# 或者，如果您想查看 Binlog 文件的更多内容，可以不指定 stop-position
# mysqlbinlog --database=airlinedb --start-position=1400 "S:/MySQL/Data/MySQL Server 9.0/Data/ROBIN-bin.000023"

# 为了更详细地看到 ROW 格式的数据变动，可能需要添加 --verbose 或 --base64-output=DECODE-ROWS 选项
mysqlbinlog --database=airlinedb --verbose "S:/MySQL/Data/MySQL Server 9.0/Data/ROBIN-bin.000023"

# 注意：执行 mysqlbinlog 可能需要数据库用户名和密码，取决于您的配置
# mysqlbinlog -u root -p --database=airlinedb --verbose "S:/MySQL/Data/MySQL Server 9.0/Data/ROBIN-bin.000023"