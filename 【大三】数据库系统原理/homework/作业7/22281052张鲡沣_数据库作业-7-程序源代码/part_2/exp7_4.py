import pymysql
import time
import csv
import random
import string
import sys

# --- 数据库连接参数 ---
DB_HOST = 'localhost'
DB_PORT = 3306
DB_USER = 'root'
DB_PASSWORD = 'ww-23451'
DB_NAME = 'airlinedb'

# --- 实验配置 ---
RESULT_FILE = 'query_performance.csv'  # 结果记录文件路径
# 定义需要测试的数据规模 (行数) 1千, 1万, 5万, 10万, 50万, 100万
DATA_SCALES = [1000, 10000, 50000, 100000, 500000, 1000000]
TARGET_NAME = "Matthew"
NUMBER_OF_QUERIES_PER_SCALE = 30

# --- 基础 Passenger 数据样本 ---
BASE_PASSENGER_DATA = [
    ('110101199001011234', 'Zhangsan', 30, '13800138000'),
    ('110101199002022345', 'Lisi', 28, '13900139000'),
    ('110101198810243608', 'Sarah', 31, '+1-009-486-7233x49762'),
    ('110101196803223943', 'Becky', 41, '928.360.5914x489'),
    ('110101197507058250', 'Erin', 42, '267.199.0167x98313'),
    ('110101198411164376', 'Lindsey', 39, '(247)989-2111x256'),
    ('110101195011276882', 'Rachel', 50, '(695)853-1407x0976'),
    ('110101196909127547', 'Scott', 37, '001-153-608-6315'),
    ('110101198610289070', 'Shirley', 50, '(132)996-0514'),
    ('110101199506209367', 'Matthew', 34, '339.628.9836x7628'),
    ('110101198709081849', 'Joshua', 50, '643.108.8938'),
    ('110101199103086642', 'James', 46, '428.095.5648'),
    ('110101199806282974', 'Erin', 63, '997-946-5506x277'),
    ('110101199602114217', 'Hayley', 44, '309-454-1411x140'),
    ('110101198909015468', 'Jamie', 62, '(032)027-5531x1870'),
    ('110101199806092967', 'Spencer', 69, '001-214-217-8565x2501'),
    ('110101195710268104', 'Matthew', 57, '3250111485'),
    ('110101196205083417', 'Jillian', 62, '001-037-770-3037x77578'),
    ('110101198908252802', 'Adam', 70, '001-674-825-7096'),
    ('110101195902078356', 'Angelica', 39, '671.252.2284x988'),
    ('110101199407095228', 'Henry', 51, '(484)693-2230x43443'),
    ('110101197702183195', 'Eric', 25, '(955)463-7007x91646'),
    ('110101197212145297', 'Jonathon', 54, '001-403-902-1744x8060'),
    ('110101195010215457', 'Robin', 42, '2130427306'),
    ('110101199407142760', 'Angela', 30, '191-603-1317'),
    ('110101199606058320', 'Cory', 65, '199-279-8019x342'),
    ('110101198910026821', 'Cindy', 68, '057.053.6953x57258'),
    ('110101197404029144', 'Cynthia', 65, '8588019068'),
    ('110101199806024063', 'Dorothy', 52, '815.165.9534x0806'),
    ('110101195405286187', 'Mary', 70, '572.245.9752x801'),
    ('110101199805127060', 'Brandon', 56, '+1-306-591-1181x8776'),
    ('110101196407104603', 'Anthony', 54, '001-461-627-5292'),
    ('110101198610116271', 'Chris', 22, '6369459526'),
    ('110101196009264879', 'Candice', 59, '+1-865-973-5344x0720'),
    ('110101197401175503', 'David', 28, '843.438.0606'),
    ('110101196010073093', 'Amber', 38, '724.764.6974x6847'),
    ('110101198208177794', 'Monica', 69, '(759)453-6726x076'),
    ('110101197011228296', 'Alexander', 43, '011.380.8012x255'),
    ('110101195603061279', 'Patrick', 42, '(746)521-7149x5387'),
    ('110101196206102759', 'Belinda', 41, '+1-922-270-8375x211'),
    ('110101197204248910', 'Christopher', 53, '+1-242-372-4582'),
    ('110101198306273248', 'Earl', 23, '257-651-7307'),
    ('110101198312118306', 'Mallory', 40, '1729969372'),
    ('110101195510276691', 'Sheryl', 68, '042.636.5506'),
    ('110101198908196586', 'Sherry', 22, '(957)088-6953'),
    ('110101197607234259', 'Cynthia', 49, '001-136-356-1089'),
    ('110101198502083115', 'Cameron', 67, '881-408-4736x2532'),
    ('110101195510198228', 'Kimberly', 28, '639.453.5941x8088'),
    ('110101197906032146', 'Michael', 69, '(774)996-3806'),
    ('110101199611172474', 'Crystal', 38, '(884)917-4311x866'),
    ('110101197705159207', 'Tara', 30, '(906)247-7268x7692'),
    ('110101198603093949', 'Jared', 39, '001-975-440-0365x55372')
]
# 样本数据集中Passenger记录总数
BASE_DATA_SIZE = len(BASE_PASSENGER_DATA)


# --- 数据库操作函数 ---
def get_connection():
    """获取数据库连接"""
    try:
        conn = pymysql.connect(
            host=DB_HOST,
            port=DB_PORT,
            user=DB_USER,
            password=DB_PASSWORD,
            database=DB_NAME,
            charset='utf8mb4',
            cursorclass=pymysql.cursors.DictCursor  # 使用字典游标，结果以字典形式返回
        )
        return conn
    except pymysql.MySQLError as e:
        print(f"数据库连接失败: {e}", file=sys.stderr)
        return None


def execute_sql(conn, sql, params=None):
    """
    执行单个 SQL 语句 (不返回结果集)，失败时抛出 pymysql.MySQLError 异常。
    """
    if not conn:
        raise pymysql.MySQLError(
            "Database connection is None, cannot execute SQL.")
    try:
        with conn.cursor() as cursor:
            cursor.execute(sql, params)
            conn.commit()
            return True
    except pymysql.MySQLError as e:
        raise e

# --- 实验数据准备函数 ---


def truncate_passenger_table(conn):
    """
    清空 Passenger 表，临时禁用外键检查以解决引用问题。返回 True 表示成功，False 表示失败。
    """
    print("正在清空 Passenger 表...")
    if not conn:
        return False

    try:
        with conn.cursor() as cursor:
            cursor.execute("SET FOREIGN_KEY_CHECKS = 0;")  # 临时禁用外键约束检查
            conn.commit()

            # 执行 TRUNCATE TRUNCATE会清空表中的所有行，但表结构及其约束、索引等保持不变
            cursor.execute("TRUNCATE TABLE Passenger")
            conn.commit()

            # 重新启用外键约束检查
            cursor.execute("SET FOREIGN_KEY_CHECKS = 1;")
            conn.commit()

        print("Passenger 表已清空.")
        return True
    except pymysql.MySQLError as e:
        print(f"清空 Passenger 表失败: {e}", file=sys.stderr)
        try:  # 失败，但是也要尝试重新启用外键检查，防止数据库状态异常
            with conn.cursor() as cursor:
                cursor.execute("SET FOREIGN_KEY_CHECKS = 1;")
                conn.commit()
        except pymysql.MySQLError as cleanup_e:
            print(
                f"清空失败后重新启用 FOREIGN_KEY_CHECKS 失败: {cleanup_e}", file=sys.stderr)
        return False


def insert_scaled_passenger_data(conn, count, base_data):
    """
    通过重复基础数据样本并修改主键来插入指定数量的 Passenger 数据。返回 True 表示成功，False 表示失败。
    """
    print(f"正在插入 {count} 条 Passenger 数据 (基于 {BASE_DATA_SIZE} 条样本)...")
    if not conn:
        return False

    sql = "INSERT INTO Passenger (id_card, passname, age, phone) VALUES (%s, %s, %s, %s)"
    data_to_insert = []

    # 改进的 ID 生成策略：确保唯一性和长度限制
    # 策略：'P' + (时间戳的后几位) + (当前序号，补齐到足够位数)
    # 例如：P + 123456 + 0000001 (14位，在VARCHAR(20)范围内)
    timestamp_part_for_id = str(int(time.time() * 1000) %
                                1000000).zfill(6)  # 时间戳后6位，补0

    # 序号部分需要足够的位数来容纳最大规模 (1,000,000 需要 7 位)
    counter_padding_length = len(str(DATA_SCALES[-1]))  # 确保能覆盖最大规模的序号位数

    for i in range(count):
        base_record_index = i % BASE_DATA_SIZE
        original_id, name, age, phone = base_data[base_record_index]

        # 组合生成新的唯一 id_card
        new_id_card = f"P{timestamp_part_for_id}{str(i).zfill(counter_padding_length)}"

        # 确保最终 ID 不超过 VARCHAR(20) 的限制
        # 新策略下总长度为 1 (P) + 6 (timestamp) + counter_padding_length (max 7) = 14 或更少，满足要求
        if len(new_id_card) > 20:  # 理论上不应该发生，但作为安全检查
            new_id_card = new_id_card[:20]

        data_to_insert.append((new_id_card, name, age, phone))

    # 批量插入并分批提交
    BATCH_SIZE = 2000  # 每批插入的行数
    start_time = time.perf_counter()

    try:
        with conn.cursor() as cursor:
            conn.autocommit(False)  # 禁用自动提交，以提高插入效率

            for i in range(0, count, BATCH_SIZE):
                batch = data_to_insert[i: i + BATCH_SIZE]
                if not batch:  # 防止最后一批为空
                    break

                cursor.executemany(sql, batch)
                conn.commit()  # 提交当前批次的事务

        end_time = time.perf_counter()
        print(f"数据插入完成，耗时: {(end_time - start_time) * 1000:.3f} ms")
        return True
    except pymysql.MySQLError as e:
        print(f"插入数据失败: {e}", file=sys.stderr)
        conn.rollback()
        return False  # 返回 False 表示插入失败
    finally:
        conn.autocommit(True)  # 恢复自动提交为 True


# --- 索引管理函数 ---
def create_passenger_name_index(conn):
    """创建 Passenger 表 passname 字段上的索引"""
    index_name = "idx_passenger_passname"
    print(f"正在创建索引 {index_name}...")
    if not conn:
        return False

    try:  # 先尝试删除，忽略不存在的错误
        execute_sql(conn, f"DROP INDEX {index_name} ON Passenger")
        print(f"旧索引 {index_name} 已删除 (如果存在).")
    except pymysql.MySQLError as e:
        if e.args[0] == 1091:
            print(f"索引 {index_name} 不存在，无需删除.")
        else:
            print(f"删除索引时发生意外错误: {e}", file=sys.stderr)
    except Exception as e:
        print(f"删除索引时发生未知错误: {e}", file=sys.stderr)

    sql = f"CREATE INDEX {index_name} ON Passenger (passname)"
    try:
        execute_sql(conn, sql)
        print(f"索引 {index_name} 已创建在 Passenger(passname) 上.")
        return True
    except pymysql.MySQLError as e:
        print(f"创建索引失败: {e}", file=sys.stderr)
        return False


def drop_passenger_name_index(conn):
    """删除 Passenger 表 passname 字段上的索引"""
    index_name = "idx_passenger_passname"
    print(f"正在删除索引 {index_name}...")
    if not conn:
        return False

    sql = f"DROP INDEX {index_name} ON Passenger"
    try:
        execute_sql(conn, sql)
        print(f"索引 {index_name} 已删除.")
        return True
    except pymysql.MySQLError as e:
        if e.args[0] == 1091:
            print(f"索引 {index_name} 不存在，无需删除.")
            return False
        else:
            print(f"删除索引失败: {e}", file=sys.stderr)
            return False
    except Exception as e:
        print(f"删除索引时发生未知错误: {e}", file=sys.stderr)
        return False


# --- 查询测试与结果记录函数 ---
def run_query_test(conn, scale, target_name, index_exists):
    """运行查询测试并记录耗时"""
    sql = "SELECT * FROM Passenger WHERE passname = %s"

    query_times_millis = []

    print(f"正在执行 {NUMBER_OF_QUERIES_PER_SCALE} 次查询 (针对 '{target_name}')...")
    if not conn:
        return

    try:
        with conn.cursor() as cursor:
            for i in range(NUMBER_OF_QUERIES_PER_SCALE):  # 执行多次查询并记录耗时
                start_time = time.perf_counter()  # 参数化查询，注意参数必须是元组 (即使只有一个元素)
                # 遍历结果集以确保数据库实际执行了查询并返回了所有匹配的行
                cursor.execute(sql, (target_name,))
                results = cursor.fetchall()  # 获取所有结果
                end_time = time.perf_counter()
                query_time_millis = (end_time - start_time) * 1000  # 记录毫秒
                query_times_millis.append(query_time_millis)
                # print(f"  查询 {i+1}/{NUMBER_OF_QUERIES_PER_SCALE} 耗时: {query_time_millis:.3f} ms, 找到 {len(results)} 条记录.") # 打印每次查询耗时和找到的记录数

            average_time_millis = sum(
                query_times_millis) / NUMBER_OF_QUERIES_PER_SCALE

            print(f"平均查询耗时: {average_time_millis:.3f} ms")

            try:
                with open(RESULT_FILE, 'a', newline='', encoding='utf-8') as csvfile:
                    writer = csv.writer(csvfile)
                    # 记录数据规模，索引是否存在(布尔值)，平均耗时
                    writer.writerow(
                        [scale, index_exists, f"{average_time_millis:.3f}"])
            except Exception as e:
                print(f"记录结果到文件失败: {e}", file=sys.stderr)
    except pymysql.MySQLError as e:
        print(f"执行查询测试失败: {e}", file=sys.stderr)


# --- 主程序逻辑 ---

if __name__ == "__main__":
    print("22281052 索引实验开始")

    # 初始化结果文件头部
    try:
        with open(RESULT_FILE, 'w', newline='', encoding='utf-8') as csvfile:  # 'w' 表示覆盖模式
            writer = csv.writer(csvfile)
            writer.writerow(["DataScale", "IndexExists", "QueryTimeMillis"])
        print(f"结果文件 {RESULT_FILE} 已初始化.")
    except Exception as e:
        print(f"无法初始化结果文件: {e}", file=sys.stderr)
        sys.exit(1)

    conn = get_connection()
    if conn:
        try:
            print("数据库连接成功.")
            # --- 准备基础数据 (如果需要) ---
            # 您的 Passenger 表本身没有外键。但是Flight 表的数据需要 Airport 和 Airline，
            # 这里专注于 Passenger 表的实验，因此不强制插入其他表的数据。

            if not BASE_PASSENGER_DATA:
                print("错误: BASE_PASSENGER_DATA 样本数据为空，无法进行实验。", file=sys.stderr)
                sys.exit(1)

            print(f"已加载 {BASE_DATA_SIZE} 条基础 Passenger 数据样本.")

            target_name_exists_in_sample = any(
                record[1] == TARGET_NAME for record in BASE_PASSENGER_DATA)
            if not target_name_exists_in_sample:
                print(
                    f"警告: 查询目标姓名 '{TARGET_NAME}' 不存在于基础样本数据中。请修改 TARGET_NAME。", file=sys.stderr)

            # --- 循环测试不同数据规模 ---
            for scale in DATA_SCALES:
                if scale < BASE_DATA_SIZE:
                    print(
                        f"\n--- 数据规模 {scale} 小于基础样本数量 {BASE_DATA_SIZE}，跳过 ---")
                    continue

                print(f"\n--- 测试数据规模: {scale} ---")

                if not truncate_passenger_table(conn):
                    print(
                        f"无法清空 Passenger 表，跳过数据规模 {scale} 的测试。", file=sys.stderr)
                    continue

                # 插入指定数量的 Passenger 数据，基于样本
                if not insert_scaled_passenger_data(conn, scale, BASE_PASSENGER_DATA):
                    print(f"数据插入失败，跳过数据规模 {scale} 的查询测试。", file=sys.stderr)
                    continue

                # --- 无索引测试 ---
                print("\n--- 无索引查询测试 ---")
                drop_passenger_name_index(conn)  # 确保没有索引
                run_query_test(conn, scale, TARGET_NAME, False)

                # --- 有索引测试 ---
                print("\n--- 有索引查询测试 ---")
                create_passenger_name_index(conn)  # 创建索引
                run_query_test(conn, scale, TARGET_NAME, True)

            print("\n所有数据规模测试完成.")

        except Exception as e:
            print(f"实验过程中发生错误: {e}", file=sys.stderr)
            try:
                if conn and not conn.get_autocommit():
                    conn.rollback()
                if conn:
                    with conn.cursor() as cursor:
                        cursor.execute("SET FOREIGN_KEY_CHECKS = 1;")
                        conn.commit()
            except Exception as cleanup_e:
                print(f"实验错误后清理失败: {cleanup_e}", file=sys.stderr)
        finally:
            if conn:
                conn.close()
                print("数据库连接已关闭.")
    else:
        print("无法进行索引实验，数据库连接失败。", file=sys.stderr)

    print(f"\n索引实验结束. 结果记录在 {RESULT_FILE}")
