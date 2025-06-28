CREATE DATABASE homework;
USE homework;

-- S表（供应商表）
CREATE TABLE S (
  SNO CHAR(2) PRIMARY KEY,
  SNAME VARCHAR(20),
  S_STATUS INT,
  CITY VARCHAR(20)
);

-- P表（零件表）
CREATE TABLE P (
  PNO CHAR(2) PRIMARY KEY,
  PNAME VARCHAR(20),
  COLOR VARCHAR(10),
  P_WEIGHT INT
);

-- J表（工程项目表）
CREATE TABLE J (
  JNO CHAR(2) PRIMARY KEY,
  JNAME VARCHAR(20),
  CITY VARCHAR(20)
);

-- SPJ表（供应情况表）
CREATE TABLE SPJ (
  SNO CHAR(2),
  PNO CHAR(2),
  JNO CHAR(2),
  QTY INT,
  PRIMARY KEY (SNO, PNO, JNO),
  FOREIGN KEY (SNO) REFERENCES S(SNO),
  FOREIGN KEY (PNO) REFERENCES P(PNO),
  FOREIGN KEY (JNO) REFERENCES J(JNO)
);

-- S表数据
INSERT INTO S (SNO, SNAME, S_STATUS, CITY) VALUES
  ('S1', '精益', 20, '天津'),
  ('S2', '盛锡', 10, '北京'),
  ('S3', '东方红', 30, '北京'),
  ('S4', '丰泰盛', 20, '天津'),
  ('S5', '为民', 30, '上海');

-- P表数据
INSERT INTO P (PNO, PNAME, COLOR, P_WEIGHT) VALUES
  ('P1', '螺母', '红', 12),
  ('P2', '螺栓', '绿', 17),
  ('P3', '螺丝刀', '蓝', 14),
  ('P4', '螺丝刀', '红', 14),
  ('P5', '凸轮', '蓝', 40),
  ('P6', '齿轮', '红', 30);

-- J表数据
INSERT INTO J (JNO, JNAME, CITY) VALUES
  ('J1', '三建', '北京'),
  ('J2', '一汽', '长春'),
  ('J3', '弹簧厂', '天津'),
  ('J4', '造船厂', '天津'),
  ('J5', '机车厂', '唐山'),
  ('J6', '无线电厂', '常州'),
  ('J7', '半导体厂', '南京');

-- SPJ表数据
INSERT INTO SPJ (SNO, PNO, JNO, QTY) VALUES
  ('S1', 'P1', 'J1', 200),
  ('S1', 'P1', 'J3', 100),
  ('S1', 'P1', 'J4', 700),
  ('S1', 'P2', 'J2', 100),
  ('S2', 'P3', 'J1', 400),
  ('S2', 'P3', 'J2', 200),
  ('S2', 'P3', 'J4', 500),
  ('S2', 'P3', 'J5', 400),
  ('S2', 'P5', 'J1', 400),
  ('S2', 'P5', 'J2', 100),
  ('S3', 'P1', 'J1', 200),
  ('S3', 'P3', 'J1', 200),
  ('S4', 'P5', 'J1', 100),
  ('S4', 'P6', 'J3', 300),
  ('S4', 'P6', 'J4', 200),
  ('S5', 'P2', 'J4', 100),
  ('S5', 'P3', 'J1', 200),
  ('S5', 'P6', 'J2', 200),
  ('S5', 'P6', 'J4', 500);

-- 查询数据
-- 求供应工程 J1 零件的供应商代码 SNO
SELECT DISTINCT SNO
FROM SPJ
WHERE JNO = 'J1';

-- 求供应工程 J1 零件 P1 的供应商代码 SNO
SELECT DISTINCT SNO
FROM SPJ
WHERE JNO = 'J1' AND PNO = 'P1';

-- 求供应工程 J1 零件为红色的供应商代码 SNO
SELECT DISTINCT SNO
FROM SPJ
WHERE JNO = 'J1'
  AND PNO IN(
    SELECT PNO
    FROM P
    WHERE COLOR = '红'
  );

-- 求没有使用天津供应商生产的红色零件的工程号 JNO
SELECT DISTINCT JNO
FROM SPJ
WHERE JNO NOT IN (
    SELECT JNO
    FROM SPJ
    WHERE SNO IN (
        SELECT SNO
        FROM S
        WHERE CITY = '天津'
      )
      AND PNO IN (
        SELECT PNO
        FROM P
        WHERE COLOR = '红'
      )
  );

-- 求至少使用了与供应商 S1 所供应的全部零件相同零件号的工程号 JNO
-- 方法1
SELECT DISTINCT SPJ1.JNO
FROM SPJ AS SPJ1
WHERE NOT EXISTS (
  SELECT *
  FROM SPJ AS SPJ2
  WHERE SPJ2.SNO = 'S1'
    AND NOT EXISTS (
      SELECT *
      FROM SPJ AS SPJ3
      WHERE SPJ3.JNO = SPJ1.JNO
        AND SPJ3.PNO = SPJ2.PNO
    )
);

-- 方法2
SELECT DISTINCT JNO
FROM SPJ AS SPJ1
WHERE NOT EXISTS (
        SELECT PNO
        FROM SPJ
        WHERE SNO = 'S1'
        EXCEPT
        SELECT PNO
        FROM SPJ AS SPJ2
        WHERE SPJ2.JNO = SPJ1.JNO
    );