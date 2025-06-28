-- 1. 找出所有供应商的姓名和所在城市
SELECT SNAME,
    CITY
FROM S;

-- 2. 找出所有零件的名称、颜色、重量
SELECT PNAME,
    COLOR,
    P_WEIGHT
FROM P;

-- 3. 找出使用供应商 S1 所供应零件的工程代码
SELECT DISTINCT JNO
FROM SPJ
WHERE SNO = 'S1';

-- 4. 找出工程项目 J2 使用的各种零件的名称及其数量
SELECT P.PNAME,
    SPJ.QTY
FROM P.SPJ
WHERE P.PNO = SPJ.PNO
    AND SPJ.JNO = 'J2';

-- 5. 找出上海厂商供应的所有零件代码
SELECT DISTINCT PNO
FROM SPJ
WHERE SNO IN (
        SELECT SNO
        FROM S
        WHERE CITY = '上海'
    );

-- 6. 找出使用上海产的零件的工程名称
SELECT DISTINCT JNAME
FROM J
WHERE JNO IN (
        SELECT JNO
        FROM SPJ
        WHERE SNO IN (
                SELECT SNO
                FROM S
                WHERE CITY = '上海'
            )
    );

-- 7. 找出没有使用天津产的零件的工程代码
SELECT DISTINCT JNO
FROM J
WHERE NOT EXISTS (
        SELECT *
        FROM SPJ
        WHERE SPJ.JNO = J.JNO
            AND SPJ.SNO IN (
                SELECT SNO
                FROM S
                WHERE CITY = '天津'
            )
    );

-- 8. 把全部红色零件的颜色改成蓝色
UPDATE P
SET COLOR = '蓝'
WHERE COLOR = '红';

-- 9. 把由 S5 供给 J2 的零件 P6 改为由 S3 供应
UPDATE SPJ
SET SNO = 'S3'
WHERE SNO = 'S5'
    AND JNO = 'J4'
    AND PNO = 'P6';
    
-- 10. 删除 S2 的所有记录（先删 SPJ，再删 S）
DELETE FROM SPJ
WHERE SNO = 'S2';
DELETE FROM S
WHERE SNO = 'S2';

-- 11. 插入 (S2, J6, P4, 200) 到供应情况表
INSERT INTO SPJ (SNO, JNO, PNO, QTY)
VALUES ('S2', 'J6', 'P4', 200);