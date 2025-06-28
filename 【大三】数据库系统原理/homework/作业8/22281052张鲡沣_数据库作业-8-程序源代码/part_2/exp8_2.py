import pymysql
import time
import threading
import sys
import decimal

# --- 数据库连接参数 ---
DB_CONFIG = {
    'host': 'localhost',
    'port': 3306,
    'user': 'root',
    'password': '密码', 
    'database': 'airlinedb',
    'charset': 'utf8mb4',
    'cursorclass': pymysql.cursors.DictCursor 
}

# 用于在多线程中同步打印输出，避免输出混乱
print_lock = threading.Lock()

# --- 辅助函数 ---
def create_db_connection(db_config):
    """创建并返回一个数据库连接，禁用自动提交"""
    try:
        conn = pymysql.connect(**db_config)
        conn.autocommit(False)  # 禁用自动提交，手动控制事务
        return conn
    except pymysql.MySQLError as e:
        with print_lock:
            print(f"数据库连接失败: {e}", file=sys.stderr)
        return None

def setup_db_and_table(conn):
    """设置数据库和TestBalance表，并插入初始数据"""
    try:
        with conn.cursor() as cursor:
            # 确保表结构存在，并且每次测试前清空并重新插入初始数据
            cursor.execute("TRUNCATE TABLE TestBalance;") # 清空表
            cursor.execute("INSERT INTO TestBalance (id, account_name, balance) VALUES (1, 'Alice', 1000.00);")
            cursor.execute("INSERT INTO TestBalance (id, account_name, balance) VALUES (2, 'Bob', 500.00);")
        conn.commit()
        with print_lock:
            print("数据库和TestBalance表已初始化，并插入初始数据。")
        return True
    except pymysql.MySQLError as e:
        with print_lock:
            print(f"初始化数据库和表失败: {e}", file=sys.stderr)
        return False

def get_balance(conn, account_id, client_name):
    """查询并打印指定账户的余额"""
    try:
        with conn.cursor() as cursor:
            cursor.execute(f"SELECT balance FROM TestBalance WHERE id = {account_id};")
            result = cursor.fetchone()
            if result:
                with print_lock:
                    print(f"[{client_name}] 查询账户 {account_id} 余额: {result['balance']:.2f}")
                return result['balance']
            else:
                with print_lock:
                    print(f"[{client_name}] 账户 {account_id} 不存在。")
                return None
    except pymysql.MySQLError as e:
        with print_lock:
            print(f"[{client_name}] 查询余额时出错: {e}", file=sys.stderr)
        return None

def update_balance(conn, account_id, amount, client_name):
    """更新指定账户的余额"""
    try:
        with print_lock:
            print(f"[{client_name}] 尝试更新账户 {account_id}，金额: {'+' if amount > 0 else ''}{amount:.2f}")
        with conn.cursor() as cursor:
            rows_affected = cursor.execute(f"UPDATE TestBalance SET balance = balance + {amount} WHERE id = {account_id};")
        with print_lock:
            if rows_affected > 0:
                print(f"[{client_name}] 成功更新账户 {account_id}。")
            else:
                print(f"[{client_name}] 未能更新账户 {account_id} (可能账户不存在或无变化)。")
        return True
    except pymysql.MySQLError as e:
        with print_lock:
            print(f"[{client_name}] 更新余额时出错: {e}", file=sys.stderr)
        return False

def insert_account(conn, account_id, account_name, balance, client_name):
    """插入一个新账户"""
    try:
        with print_lock:
            print(f"[{client_name}] 尝试插入账户 {account_id} ({account_name}, {balance:.2f})...")
        with conn.cursor() as cursor:
            cursor.execute(f"INSERT INTO TestBalance (id, account_name, balance) VALUES ({account_id}, '{account_name}', {balance:.2f});")
        with print_lock:
            print(f"[{client_name}] 成功插入账户 {account_id}。")
        return True
    except pymysql.MySQLError as e:
        with print_lock:
            print(f"[{client_name}] 插入账户时出错: {e}", file=sys.stderr)
        return False

def count_balance_gt_zero(conn, client_name):
    """查询余额大于0的账户数量"""
    try:
        with print_lock:
            print(f"[{client_name}] 查询余额大于0的账户数量...")
        with conn.cursor() as cursor:
            cursor.execute("SELECT COUNT(*) AS count FROM TestBalance WHERE balance > 0;")
            result = cursor.fetchone()
            count = result['count']
        with print_lock:
            print(f"[{client_name}] 查询结果: {count} 个账户余额大于0。")
        return count
    except pymysql.MySQLError as e:
        with print_lock:
            print(f"[{client_name}] 查询账户数量时出错: {e}", file=sys.stderr)
        return None

# --- 并发场景测试函数 ---

def run_test_scenario(test_name, isolation_level_str, client_a_logic, client_b_logic):
    """
    运行一个并发测试场景。
    :param test_name: 场景名称
    :param isolation_level_str: 隔离级别字符串 (如 'READ UNCOMMITTED')
    :param client_a_logic: 客户端A的逻辑函数
    :param client_b_logic: 客户端B的逻辑函数
    """
    with print_lock:
        print(f"\n{'='*80}\n开始测试场景: {test_name}\n隔离级别: {isolation_level_str}\n{'='*80}")

    conn_a = create_db_connection(DB_CONFIG)
    conn_b = create_db_connection(DB_CONFIG)

    if not conn_a or not conn_b:
        with print_lock:
            print("未能建立所有数据库连接，跳过此测试。")
        return

    # 重置数据，确保每个测试场景从干净的状态开始
    if not setup_db_and_table(conn_a): # 只需一个连接重置，因为是COMMIT后生效
        with print_lock:
            print("数据重置失败，跳过此测试。")
        conn_a.close()
        conn_b.close()
        return

    # 设置每个会话的隔离级别
    try:
        with conn_a.cursor() as cursor_a, conn_b.cursor() as cursor_b:
            cursor_a.execute(f"SET SESSION TRANSACTION ISOLATION LEVEL {isolation_level_str};")
            cursor_b.execute(f"SET SESSION TRANSACTION ISOLATION LEVEL {isolation_level_str};")
        conn_a.commit() # 提交隔离级别设置
        conn_b.commit()
    except pymysql.MySQLError as e:
        with print_lock:
            print(f"设置隔离级别失败: {e}，跳过此测试。", file=sys.stderr)
        conn_a.close()
        conn_b.close()
        return

    # 用于线程间同步的事件
    event_a_ready = threading.Event() # A准备好
    event_b_ready = threading.Event() # B准备好
    event_a_signal_b = threading.Event() # A给B信号
    event_b_signal_a = threading.Event() # B给A信号
    event_a_done = threading.Event() # A完成
    event_b_done = threading.Event() # B完成

    # 创建并启动线程
    thread_a = threading.Thread(target=client_a_logic, args=(conn_a, "客户端A", 
                                event_a_ready, event_b_ready, event_a_signal_b, event_b_signal_a, event_a_done, event_b_done))
    thread_b = threading.Thread(target=client_b_logic, args=(conn_b, "客户端B", 
                                event_b_ready, event_a_ready, event_b_signal_a, event_a_signal_b, event_b_done, event_a_done))

    thread_a.start()
    thread_b.start()

    thread_a.join() # 等待线程A完成
    thread_b.join() # 等待线程B完成

    # 关闭连接
    # conn_a.close()
    # conn_b.close()

    with print_lock:
        print(f"\n测试场景: {test_name} 结束。\n{'='*80}")

# --- 客户端逻辑函数 (每个并发问题对应一对) ---

# --- 1. 脏读 (Dirty Read) 演示 ---

# 场景1.1：脏读 (READ UNCOMMITTED)
def client_a_dirty_read(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set() # 线程A准备好
        other_ready.wait() # 等待线程B准备好
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin() # START TRANSACTION

        update_balance(conn, 1, -200.00, name) # Alice余额变为800.00，未提交
        with print_lock: print(f"[{name}] 更新Alice余额为800.00，未提交。")
        
        my_signal_other.set() # 通知客户端B可以读取脏数据了
        other_signal_my.wait() # 等待客户端B读完脏数据

        with print_lock: print(f"[{name}] 回滚事务，Alice余额将恢复为1000.00。")
        conn.rollback() 
        
        my_signal_other.set() # 通知客户端B可以再次读取了
        other_signal_my.wait() # 等待客户端B完成
        
        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

def client_b_dirty_read(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin() # START TRANSACTION

        other_signal_my.wait() # 等待客户端A更新并通知
        get_balance(conn, 1, name) # 第一次读取 Alice 余额，期望读到脏数据 (800.00)

        my_signal_other.set() # 通知客户端A已读完脏数据
        other_signal_my.wait() # 等待客户端A回滚并通知

        get_balance(conn, 1, name) # 第二次读取 Alice 余额，期望读到回滚后的数据 (1000.00)
        
        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit() 
        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

# 场景1.2：防止脏读 (READ COMMITTED)
def client_a_prevent_dirty_read(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        update_balance(conn, 1, -200.00, name) # Alice余额变为800.00，未提交
        with print_lock: print(f"[{name}] 更新Alice余额为800.00，未提交。")
        
        my_signal_other.set() # 通知客户端B可以读取了
        other_signal_my.wait() # 等待客户端B读完

        with print_lock: print(f"[{name}] 回滚事务，Alice余额将恢复为1000.00。")
        conn.rollback()
        
        my_signal_other.set() # 通知客户端B可以再次读取了
        other_signal_my.wait() # 等待客户端B完成

        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

def client_b_prevent_dirty_read(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        other_signal_my.wait() # 等待客户端A更新并通知
        get_balance(conn, 1, name) # 第一次读取 Alice 余额，期望读到原始值 (1000.00)

        my_signal_other.set() # 通知客户端A已读完
        other_signal_my.wait() # 等待客户端A回滚并通知

        get_balance(conn, 1, name) # 第二次读取 Alice 余额，期望读到原始值 (1000.00)
        
        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit() 
        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

# --- 2. 不可重复读 (Non-repeatable Read) 演示 ---

# 场景2.1：不可重复读 (READ COMMITTED)
def client_a_non_repeatable_read(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        get_balance(conn, 1, name) # 第一次读取 Alice 余额 (期望1000.00)
        
        my_signal_other.set() # 通知客户端B可以更新并提交了
        other_signal_my.wait() # 等待客户端B更新并提交

        get_balance(conn, 1, name) # 第二次读取 Alice 余额，期望读到已提交的更新 (900.00)
        
        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit()
        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

def client_b_non_repeatable_read(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        other_signal_my.wait() # 等待客户端A第一次读取
        update_balance(conn, 1, -100.00, name) # Alice余额变为900.00
        with print_lock: print(f"[{name}] 提交更新Alice余额到900.00。")
        conn.commit()

        my_signal_other.set() # 通知客户端A可以进行第二次读取
        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

# 场景2.2：防止不可重复读 (REPEATABLE READ)
def client_a_prevent_non_repeatable_read(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        get_balance(conn, 1, name) # 第一次读取 Alice 余额 (期望1000.00)
        
        my_signal_other.set() # 通知客户端B可以更新并提交了
        other_signal_my.wait() # 等待客户端B更新并提交

        get_balance(conn, 1, name) # 第二次读取 Alice 余额，期望读到和第一次相同的值 (1000.00)
        
        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit()
        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

def client_b_prevent_non_repeatable_read(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        other_signal_my.wait() # 等待客户端A第一次读取
        update_balance(conn, 1, -100.00, name) # Alice余额变为900.00
        with print_lock: print(f"[{name}] 提交更新Alice余额到900.00。")
        conn.commit()

        my_signal_other.set() # 通知客户端A可以进行第二次读取
        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

# --- 3. 丢失修改 (Lost Update) 演示 ---

# 场景3.1：丢失修改 (READ COMMITTED 理论演示，MySQL实际会加锁阻止)
# 注意：在MySQL中，即使是READ COMMITTED，UPDATE语句也会加行锁，通常会阻止丢失修改。
# 这里的演示更多是概念性的，或者在某些不加锁的数据库/特定场景下可能发生。
# 在MySQL中，客户端B的UPDATE会阻塞直到客户端A提交。
def client_a_lost_update(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        balance = get_balance(conn, 1, name) # 读取 Alice 余额
        # 将 float 数字面量转换为 Decimal 类型
        amount_to_add = decimal.Decimal('50.00') 
        with print_lock: print(f"[{name}] 计算新余额: {balance:.2f} + {amount_to_add:.2f} = {balance + amount_to_add:.2f}")
        time.sleep(0.1) # 模拟计算延迟
        
        my_signal_other.set() # 通知客户端B可以读取和计算了
        other_signal_my.wait() # 等待客户端B完成读取和计算

        update_balance(conn, 1, +50.00, name) # 这里参数已经是数值，pymysql会处理
        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit() # 释放锁

        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

def client_b_lost_update(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        other_signal_my.wait() # 等待客户端A读取和计算
        balance = get_balance(conn, 1, name) # 读取 Alice 余额
        # 将 float 数字面量转换为 Decimal 类型
        amount_to_add = decimal.Decimal('100.00')
        with print_lock: print(f"[{name}] 计算新余额: {balance:.2f} + {amount_to_add:.2f} = {balance + amount_to_add:.2f}")
        time.sleep(0.1) # 模拟计算延迟
        
        my_signal_other.set() # 通知客户端A已读完和计算完

        with print_lock: print(f"[{name}] 尝试更新，期望会被客户端A阻塞。")
        update_balance(conn, 1, +100.00, name) # 这里参数已经是数值，pymysql会处理
        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit()

        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

# 场景3.2：防止丢失修改 (REPEATABLE READ)
# 在MySQL中，REPEATABLE READ下的UPDATE操作会加行锁，防止丢失修改。
# 这里的测试和上面的3.1在行为上会类似，因为更新操作在MySQL中默认会加锁。
# 主要的演示是说明REPEATABLE READ能自然地防止此问题。
def client_a_prevent_lost_update_rr(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        get_balance(conn, 1, name) # 读取 Alice 余额
        
        my_signal_other.set() # 通知客户端B读取
        other_signal_my.wait() # 等待客户端B读取完成

        update_balance(conn, 1, +50.00, name) # Alice余额变为1050.00，获得锁
        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit() # 释放锁

        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

def client_b_prevent_lost_update_rr(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        other_signal_my.wait() # 等待客户端A读取
        get_balance(conn, 1, name) # 读取 Alice 余额
        
        my_signal_other.set() # 通知客户端A已读完

        with print_lock: print(f"[{name}] 尝试更新，期望会被客户端A阻塞。")
        update_balance(conn, 1, +100.00, name) # Alice余额变为1150.00

        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit()
        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()


# --- 4. 幻读 (Phantom Read) 演示 ---

# 场景4.1：幻读 (READ COMMITTED)
def client_a_phantom_read(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        count1 = count_balance_gt_zero(conn, name) # 第一次查询账户数量
        
        my_signal_other.set() # 通知客户端B可以插入了
        other_signal_my.wait() # 等待客户端B插入并提交

        count2 = count_balance_gt_zero(conn, name) # 第二次查询账户数量，期望看到新插入的行
        
        if count2 > count1:
            with print_lock: print(f"[{name}] *** 发生了幻读！第二次查询看到了新插入的行。 ***")
        else:
            with print_lock: print(f"[{name}] 没有发生幻读 (不符合READ COMMITTED预期)。")

        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit()
        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

def client_b_phantom_read(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        other_signal_my.wait() # 等待客户端A第一次查询
        
        insert_account(conn, 3, 'Charlie', 200.00, name) # 插入新账户
        with print_lock: print(f"[{name}] 提交新账户插入。")
        conn.commit() # 提交新插入的行

        my_signal_other.set() # 通知客户端A可以进行第二次查询
        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

# 场景4.2：防止幻读 (REPEATABLE READ)
def client_a_prevent_phantom_read_rr(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        count1 = count_balance_gt_zero(conn, name) # 第一次查询账户数量
        
        my_signal_other.set() # 通知客户端B可以插入了 (期望B被阻塞)
        other_signal_my.wait() # 等待客户端B尝试插入 (期望B被阻塞，直到A提交)

        count2 = count_balance_gt_zero(conn, name) # 第二次查询账户数量，期望与第一次相同
        
        if count2 == count1:
            with print_lock: print(f"[{name}] *** 成功防止幻读！第二次查询结果与第一次相同。 ***")
        else:
            with print_lock: print(f"[{name}] 幻读发生 (不符合REPEATABLE READ预期)。")

        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit() # 释放锁
        my_done.set() # 通知客户端B可以继续了 (如果它被阻塞)
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

def client_b_prevent_phantom_read_rr(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        other_signal_my.wait() # 等待客户端A第一次查询并加锁
        
        with print_lock: print(f"[{name}] 尝试插入一个新账户 (ID 3, balance 200.00)...")
        with print_lock: print(f"[{name}] *** 期望此处被阻塞，直到客户端A提交。 ***")
        insert_account(conn, 3, 'Charlie', 200.00, name) # 插入新账户 (期望会被阻塞)
        
        with print_lock: print(f"[{name}] 插入完成，客户端A已提交。")
        conn.commit() # 提交新插入的行

        my_signal_other.set() # 通知客户端A已完成
        my_done.set()
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

# --- 5. 完全串行化 (SERIALIZABLE) 演示 ---
# SERIALIZABLE 级别会防止所有并发问题。我们通过幻读场景来演示其效果。
# 修改 client_a_serializable 函数
def client_a_serializable(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        count1 = count_balance_gt_zero(conn, name) # 第一次查询账户数量 (SERIALIZABLE将加范围锁)
        
        my_signal_other.set() # 通知客户端B可以插入了 (期望会被阻塞)
        other_signal_my.wait(timeout=30) # 等待客户端B尝试插入 (期望B被阻塞，直到A提交)。设置超时，避免死锁（如果逻辑有误）
                                         # **这里只是等待B的信号，实际阻塞发生在B的INSERT语句处**
                                         # (可以考虑移除这句，让B一直阻塞直到A提交)
        
        with print_lock: print(f"[{name}] 完成第一次查询和等待。")
        with print_lock: print(f"[{name}] 第二次查询余额大于0的账户数量 (期望与第一次相同)...")
        with conn.cursor() as cursor:
            cursor.execute("SELECT COUNT(*) AS count FROM TestBalance WHERE balance > 0;")
            result = cursor.fetchone()
            count2 = result['count']
        with print_lock: print(f"[{name}] 第二次查询结果: {count2} 个账户余额大于0。")
        
        if count2 == count1:
            with print_lock: print(f"[{name}] *** 成功防止幻读！第二次查询结果与第一次相同。 ***")
        else:
            with print_lock: print(f"[{name}] 幻读发生 (不符合SERIALIZABLE预期)。")

        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit() # 释放锁
        my_signal_other.set() # 释放锁后，通知客户端B可以继续了
        
        # 等待客户端B真正完成，避免主线程过早关闭连接
        other_done.wait() 
        my_done.set() # A线程完成
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

# 客户端B的逻辑不需要太多修改，它会在INSERT处自动阻塞，直到客户端A提交。
# client_b_serializable 的 my_signal_other.set() 应该在 insert_account 后执行，表示它完成了插入操作的尝试。
# 确保 client_b_serializable 在 conn.commit() 之后也 set its my_done event.

# 请确保 client_b_serializable 的 my_signal_other.set() 在它尝试 insert 之后执行，
# 并且 client_b_serializable 最后也要 set its my_done event。

# 检查 client_b_serializable 函数：
def client_b_serializable(conn, name, my_ready, other_ready, my_signal_other, other_signal_my, my_done, other_done):
    try:
        my_ready.set()
        other_ready.wait()
        
        with print_lock: print(f"[{name}] 开始事务...")
        conn.begin()

        other_signal_my.wait() # 等待客户端A第一次查询并加锁
        
        with print_lock: print(f"[{name}] 尝试插入一个新账户 (ID 3, balance 200.00)...")
        with print_lock: print(f"[{name}] *** 期望此处被阻塞，直到客户端A提交。 ***")
        insert_account(conn, 3, 'Charlie', 200.00, name) # 插入新账户 (期望会被阻塞)
        
        my_signal_other.set() # **客户端B通知A，它已经尝试插入了（或插入完成了）**

        with print_lock: print(f"[{name}] 插入完成，客户端A已提交。") # 这句将在A提交后才打印，因为B被阻塞了
        with print_lock: print(f"[{name}] 提交事务。")
        conn.commit() # 提交新插入的行

        my_done.set() # 客户端B完成
    except pymysql.MySQLError as e:
        with print_lock: print(f"[{name}] 发生错误: {e}")
        conn.rollback()
    finally:
        if conn.open: conn.close()

# --- 主程序逻辑 ---
if __name__ == "__main__":
    LOG_FILE_NAME = "concurrency_experiment_output.txt" # 定义日志文件名

    # 保存原始的标准输出流
    original_stdout = sys.stdout

    try:
        # 打开日志文件，以写入模式 ('w') 打开，如果文件不存在则创建，如果存在则清空
        with open(LOG_FILE_NAME, 'w', encoding='utf-8') as f_log:
            # 将标准输出流重定向到文件对象
            sys.stdout = f_log

            # 现在，所有的 print() 输出都会写入到 f_log 文件中
            
            main_conn = create_db_connection(DB_CONFIG)
            if not main_conn:
                # 错误信息通过 sys.stderr 输出，不受 sys.stdout 重定向影响
                # 但为了确保错误也能被记录到文件，需要手动捕获
                with original_stdout: # 临时切换回原始stdout打印错误，然后恢复
                     print(f"Error: 无法建立主数据库连接，实验终止。", file=sys.stderr)
                sys.exit(1)

            if not setup_db_and_table(main_conn):
                with original_stdout:
                     print(f"Error: 初始化数据库和表失败，实验终止。", file=sys.stderr)
                main_conn.close()
                sys.exit(1)

            main_conn.close() # 主连接只用于初始化，之后每个线程创建自己的连接

            # 所有测试场景
            scenarios = [
                # 脏读 (Dirty Read)
                ("脏读 (Dirty Read) 演示", 'READ UNCOMMITTED', client_a_dirty_read, client_b_dirty_read),
                ("防止脏读", 'READ COMMITTED', client_a_prevent_dirty_read, client_b_prevent_dirty_read),
                ("防止脏读", 'REPEATABLE READ', client_a_prevent_dirty_read, client_b_prevent_dirty_read),
                
                # 不可重复读 (Non-repeatable Read)
                ("不可重复读 (Non-repeatable Read) 演示", 'READ UNCOMMITTED', client_a_non_repeatable_read, client_b_non_repeatable_read),
                ("不可重复读 (Non-repeatable Read) 演示", 'READ COMMITTED', client_a_non_repeatable_read, client_b_non_repeatable_read),
                ("防止不可重复读", 'REPEATABLE READ', client_a_prevent_non_repeatable_read, client_b_prevent_non_repeatable_read),

                # 丢失修改 (Lost Update)
                ("丢失修改 (Lost Update) 演示 (MySQL中会阻塞)", 'READ UNCOMMITTED', client_a_lost_update, client_b_lost_update),
                ("丢失修改 (Lost Update) 演示 (MySQL中会阻塞)", 'READ COMMITTED', client_a_lost_update, client_b_lost_update),
                ("防止丢失修改 (REPEATABLE READ)", 'REPEATABLE READ', client_a_prevent_lost_update_rr, client_b_prevent_lost_update_rr),

                # 幻读 (Phantom Read)
                ("幻读 (Phantom Read) 演示", 'READ UNCOMMITTED', client_a_phantom_read, client_b_phantom_read),
                ("幻读 (Phantom Read) 演示", 'READ COMMITTED', client_a_phantom_read, client_b_phantom_read),
                ("防止幻读 (REPEATABLE READ)", 'REPEATABLE READ', client_a_prevent_phantom_read_rr, client_b_prevent_phantom_read_rr),
                
                # 完全串行化 (SERIALIZABLE)
                ("所有并发问题防范 (SERIALIZABLE)", 'SERIALIZABLE', client_a_serializable, client_b_serializable)
            ]

            for name, iso_level, client_a_logic, client_b_logic in scenarios:
                run_test_scenario(name, iso_level, client_a_logic, client_b_logic)

            # 最终验证数据
            final_conn = create_db_connection(DB_CONFIG)
            if final_conn:
                with print_lock: # 使用print_lock确保线程安全地打印
                    print(f"\n{'='*80}\n所有测试完成，最终数据状态:\n{'='*80}")
                get_balance(final_conn, 1, "最终检查")
                get_balance(final_conn, 2, "最终检查")
                get_balance(final_conn, 3, "最终检查") # 检查是否有 Charlie 账户 (根据最后一次测试的提交情况)
                final_conn.close()

            with print_lock:
                print("\n所有实验已完成。")

    except Exception as e:
        # 如果在文件操作或主逻辑中发生任何其他异常，确保原始标准输出被恢复
        sys.stdout = original_stdout 
        print(f"程序执行过程中发生未预期的错误: {e}", file=sys.stderr)
        sys.exit(1)
    finally:
        # 无论如何，确保标准输出被恢复到终端
        sys.stdout = original_stdout 
        print(f"\n实验输出已保存到: {LOG_FILE_NAME}") # 这条信息会显示在终端