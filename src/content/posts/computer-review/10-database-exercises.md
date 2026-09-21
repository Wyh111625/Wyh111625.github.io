---
title: "计算机复习 · 附录 B｜数据库综合题"
published: 2026-09-21
description: "结合职工、学生、课程与社团场景，整理 SQL 综合题模板、连接查询和 E-R 设计检查要点。"
tags: ["计算机复习","数据库","SQL","综合题"]
category: 计算机复习
lang: zh_CN
draft: false
---

> 本文属于「计算机复习」系列。[系列目录与阅读说明](/posts/computer-review/00-overview/)；文中页码指原教材 PDF 页码，Windows／Office 操作沿用 Windows 7／Office 2010 语境。

示例用于理解查询逻辑。不同数据库的字符串、日期、标识符引用和建表类型可能不同；以下尽量采用通用写法，涉及原题特殊字段名时明确转换。

## B.1 试卷 1：职工—工作—公司三表，第 231—232 页

原题使用 `EMP(E#,ENAME,AGE,SEX,ECITY)`、`WORKS(E#,C#,SALARY)`、`COMP(C#,CNAME,CITY)`。为避免 `#` 标识符引用规则差异，示例把 E# 改名 **Eid**、C# 改名 **Cid**，其含义不变；实际考试应按题设字段名和指定数据库写法填写。

### 1. 年龄超过 50 岁的女职工

```sql
SELECT Eid, Ename
FROM EMP
WHERE Age > 50 AND Sex = '女';
```

“超过”是 `>`；“以上（含）”是 `>=`；“且”用 AND。

### 2. 在“苏宁”工作、工资超过 3000 元的男性

```sql
SELECT e.Eid, e.Ename, w.Salary
FROM EMP AS e
JOIN WORKS AS w ON w.Eid = e.Eid
JOIN COMP AS c ON c.Cid = w.Cid
WHERE c.Cname = '苏宁'
  AND w.Salary > 3000
  AND e.Sex = '男';
```

EMP 取人，WORKS 取工资并联结人和公司，COMP 按公司名筛选。不能因两个表有姓名就用姓名连接。

### 3. 籍贯河南安阳且在“华联”工作的平均工资

```sql
SELECT AVG(w.Salary) AS AvgSalary
FROM EMP AS e
JOIN WORKS AS w ON w.Eid = e.Eid
JOIN COMP AS c ON c.Cid = w.Cid
WHERE e.Ecity = '河南安阳' AND c.Cname = '华联';
```

籍贯属于职工表 Ecity，公司所在地属于 COMP.City，不能混用。

### 4. 给 55 岁及以上职工在每家公司的一条工作记录加 100 元

```sql
UPDATE WORKS
SET Salary = Salary + 100
WHERE Eid IN (
    SELECT Eid FROM EMP WHERE Age >= 55
);
```

若同一职工在多家公司工作，WORKS 中相应多行都会增加 100，符合题意；不是只修改职工表。

### 5. 删除年龄超过 60 岁职工及其工作记录

```sql
DELETE FROM WORKS
WHERE Eid IN (SELECT Eid FROM EMP WHERE Age > 60);

DELETE FROM EMP
WHERE Age > 60;
```

先删除引用职工的工作记录，再删职工，避免外键冲突；真实操作应置于适合该 DBMS 的事务中。

## B.2 试卷 2：学生信息插入与修改，第 241 页

考点是 **完整列清单、字符编号、NULL、不遗漏查询结果、用唯一标识定位更新**。按原题给定的两名学生填写，NULL 不加引号。

```sql
INSERT INTO 学生表
    (班级, 学号, 姓名, 性别, 民族, 身份证号, 出生日期)
VALUES
    ('200601', '200601001', '王欣', '女', '汉',
     '530102199906252240', '1999-06-25');

INSERT INTO 学生表
    (班级, 学号, 姓名, 性别, 民族, 身份证号, 出生日期)
VALUES
    ('200602', '200602002', '张刚', '男', NULL, NULL, NULL);

SELECT * FROM 学生表
WHERE 学号 IN ('200601001', '200602002');

UPDATE 学生表
SET 民族 = '汉', 出生日期 = '1999-12-26'
WHERE 学号 = '200602002';

SELECT * FROM 学生表 WHERE 学号 = '200602002';
```

日期赋值是否要 `DATE '1999-06-25'`、转换函数等取决于数据库；上面假定可把 ISO 格式日期字符串转换到该列。原题未列完整建表定义，不擅自给缺失字段编造约束。

## B.3 试卷 3：建表并查询，第 247 页

原题给了 `TINYINT(4)` 等偏 MySQL 风格的类型。以下按这一题目风格展示：

```sql
CREATE TABLE 学生表 (
    学号 CHAR(8) PRIMARY KEY,
    姓名 CHAR(10),
    性别 CHAR(2),
    年龄 TINYINT,
    所在系 CHAR(20)
);

SELECT 学号, 姓名
FROM 学生表
WHERE 所在系 = '计算机' AND 年龄 < 20;
```

若数据实际把系名存为“计算机系”，条件字符串应相应改为 `'计算机系'`；题干没有给出数据内容，不可假定两种文本自动等价。旧 MySQL `TINYINT(4)` 的括号是显示宽度，不代表可保存四位十进制数。

## B.4 第八章综合题：没有选某门课

原书第 223 页“检索不学 C2 的学生学号”，核心是**对学生整体排除存在 C2 选课的人**。用附录前第八章表名：

```sql
SELECT s.Sno
FROM Student AS s
WHERE NOT EXISTS (
    SELECT 1 FROM SC AS sc
    WHERE sc.Sno = s.Sno AND sc.Cno = 'C2'
);
```

关系代数思路：全体学生学号集合减去选修 C2 的学生学号集合，即 `π学号(学生) − π学号(σ课程号='C2'(选课))`。

相邻同类题：查“至少选马老师一门课”，先在课程表筛教师，再连接选课和学生，最终必要时 DISTINCT 去重；查“选全部指定课程”，不能只用 IN，需要计数比较或双重 NOT EXISTS 等方法。

## B.5 第 224 页：学生—社团数据库

为便于阅读，示例用 `Student(Sno,Sname,Age,Sex)`、`Club(Cid,Cname,Leader,Place)`、`Member(Sno,Cid,JoinDate)`。Leader 参照学生主键，Member 联合主键为 (Sno,Cid)，分别关联学生与社团；不得把“负责人姓名”直接当作学号外键。

```sql
CREATE TABLE Club (
    Cid VARCHAR(8) PRIMARY KEY,
    Cname VARCHAR(60) NOT NULL,
    Leader VARCHAR(8),
    Place VARCHAR(100),
    FOREIGN KEY (Leader) REFERENCES Student(Sno)
);

CREATE TABLE Member (
    Sno VARCHAR(8),
    Cid VARCHAR(8),
    JoinDate DATE,
    PRIMARY KEY (Sno, Cid),
    FOREIGN KEY (Sno) REFERENCES Student(Sno),
    FOREIGN KEY (Cid) REFERENCES Club(Cid)
);
```

学生表按第八章建表示例取对应字段；先建 Student，再建 Club、Member。

**参加唱歌队或篮球队的学生**：

```sql
SELECT DISTINCT s.Sno, s.Sname
FROM Student AS s
JOIN Member AS m ON m.Sno = s.Sno
JOIN Club AS c ON c.Cid = m.Cid
WHERE c.Cname IN ('唱歌队', '篮球队');
```

**参加人数超过 100 的社团及其负责人**：

```sql
SELECT c.Cid, c.Cname, c.Leader
FROM Club AS c
JOIN Member AS m ON m.Cid = c.Cid
GROUP BY c.Cid, c.Cname, c.Leader
HAVING COUNT(*) > 100;
```

**每个社团人数，包含 0 人社团**：

```sql
SELECT c.Cid, c.Cname, COUNT(m.Sno) AS N
FROM Club AS c
LEFT JOIN Member AS m ON m.Cid = c.Cid
GROUP BY c.Cid, c.Cname;
```

这里用 COUNT(m.Sno)，不是 COUNT(*)，否则左连接产生的空匹配行可能把 0 人记成 1 人。

**参加人数最多的社团，包含并列第一**：

```sql
WITH Counts AS (
    SELECT c.Cid, c.Cname, COUNT(m.Sno) AS N
    FROM Club AS c
    LEFT JOIN Member AS m ON m.Cid = c.Cid
    GROUP BY c.Cid, c.Cname
)
SELECT Cname, N
FROM Counts
WHERE N = (SELECT MAX(N) FROM Counts);
```

CTE／WITH 是为清晰起见补充的写法；若课程只要求教材语法，可用同等逻辑的派生表或视图。只写降序并取第一行会漏掉并列第一。

## B.6 E-R 题的答题检查

1. 从题干找实体、属性、联系，不擅自添加没有给出的业务限制。
2. 明确每条联系两端的基数，尤其注意一对多与多对多。
3. 学生选课成绩放在选课联系中；部门电话放在部门中。
4. 标注主键、外键，联合主键用一组属性表示。
5. 先修课程用同一课程表自参照；先修课允许没有时考虑 NULL。
6. 关系模式数量不是固定答案，1:n 采用并入多端与单建联系再合并可能形成等价设计，应说明约束。

---

[系列目录与阅读说明](/posts/computer-review/00-overview/) · [上一篇：附录 A｜程序设计实操](/posts/computer-review/09-programming/) · [下一篇：附录 C｜补充考点清单](/posts/computer-review/11-exam-checklist/)
