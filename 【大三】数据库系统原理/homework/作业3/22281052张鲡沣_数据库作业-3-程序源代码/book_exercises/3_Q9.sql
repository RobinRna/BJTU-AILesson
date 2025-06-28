-- 创建视图：三建工程项目的供应情况
CREATE VIEW V_SPJ AS
SELECT SNO,
    PNO,
    QTY
FROM SPJ
WHERE JNO = (
        SELECT JNO
        FROM J
        WHERE JNAME = '三建'
    );
-- 查询1：找出三建工程项目使用的各种零件代码及其数量
SELECT PNO, QTY
FROM V_SPJ;
-- 查询2：找出供应商 S1 供应三建工程情况
SELECT *
FROM V_SPJ
WHERE SNO = 'S1';