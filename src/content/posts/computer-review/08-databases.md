---
title: "计算机复习 · 08｜数据库技术基础"
published: 2026-09-21
description: "从数据模型、键与完整性到关系代数和 SQL，系统复习数据库设计、查询、更新与事务。"
tags: ["计算机复习","数据库","SQL"]
category: 计算机复习
lang: zh_CN
draft: false
showOnHome: false
---

> 本文属于「计算机复习」系列。[第 1～8 章专题页](/computer-review/) · [系列目录与阅读说明](/posts/computer-review/00-overview/)；文中页码指原教材 PDF 页码，Windows／Office 操作沿用 Windows 7／Office 2010 语境。

**原书范围：PDF 第 197—224 页。** 原书小节沿用了“10.x”编号，但目录属第八章。本笔记统一使用第八章，并补足卷末 SQL 综合题。

## 8.1 数据、数据库、管理系统与数据库系统

- 数据：记录信息的可识别符号，可为数值、文字、图像、声音等；数据处理包含采集、存储、加工、分类、检索、传播。
- **DB 数据库**：长期存储、有组织、可共享的数据集合；**DBMS 数据库管理系统**：管理数据库的软件；**DBS 数据库系统**：数据库、DBMS、相关应用、人员、软硬件环境等构成的系统；**DBA**：数据库管理员。
- DBMS 主要功能：数据定义、查询操纵、运行控制、数据库建立维护；运行控制包括安全、完整性、并发与恢复等。
- 数据库系统特点：结构化、共享性较高、冗余较少、独立性较高、由 DBMS 统一管理控制；“冗余较少”不是绝不允许任何冗余。
- DBMS 如 Oracle、SQL Server、MySQL、PostgreSQL、Access；SQL 是语言，不是某一数据库产品。
- 数据模型通常包含 **数据结构、数据操作、完整性约束** 三部分。【第 223 页第 7 题】

## 8.2 数据模型与 E-R 图

- 概念模型面向业务和用户需求，尽量独立于具体 DBMS；逻辑模型面向某种数据库类型，常见层次、网状、关系模型。
- 层次模型：树，一个非根节点通常只有一个父节点，适合一对多；网状模型允许多个父节点；关系模型用二维表表示数据与联系。
- E-R 图三要素：**实体矩形、属性椭圆、联系菱形**。实体类型与实体实例不同，如“学生”与“某个学生”。
- 联系类型：1:1、一对多 1:n、多对多 m:n，必须由业务约束确定。例如系—教师通常 1:n，学生—课程通常 m:n。
- 联系本身可有属性：学生选某课程的“成绩”应属于选课联系，不仅是学生属性，也不仅是课程属性。
- 一门课程有先修课属于同类实体的自联系；需辨别“每课程一个先修课”不代表“每门课程最多只能作为另一门课程的先修课”。

## 8.3 关系模型术语、键与完整性

| 术语 | 含义 |
|---|---|
| 关系 | 一张符合关系要求的二维表 |
| 元组／记录 | 一行 |
| 属性／字段 | 一列 |
| 域 | 某属性允许取值的集合 |
| 元数／度 | 属性列数 |
| 基数 | 元组行数 |
| 关系模式 | 结构描述，如 Student(Sno,Sname,Age) |
| 超键 | 能唯一标识元组的属性集合，可含多余属性 |
| 候选键 | 最小超键，无多余属性 |
| 主键／主码 | 从候选键中选定的一个 |
| 外键／外码 | 参照其他／本表候选键等唯一标识的属性集合 |

- 关系中属性名区分各列，同列值属于同域；理论关系行列顺序无关，无重复元组，分量不可再分。SQL 查询结果可含重复行，与数学集合式关系要区分。
- 主键可由多列组成；一张表只能有一个主键约束，但这个键可含多个字段，也可有多个其他候选键。
- 外键不一定唯一，也可能同时属于本表主键；允许 NULL 与否由约束决定。教材“外键必然不是本表键”的说法不成立。
- **实体完整性**：主键不能重复、不能空；**参照完整性**：外键非空值应能对应被参照键；**用户定义完整性**：年龄、成绩等业务限制。
- 选课表 `SC(Sno,Cno,Grade)` 常以 `(Sno,Cno)` 为联合主键；Sno、Cno 分别参照学生、课程表。
- NULL 表示未知、缺失或不适用等，不等于数字 0、不等于空格，也不等于普通字符串 `'NULL'`。

## 8.4 关系代数

- 运算对象和结果都是关系；**五个基本运算**：并、差、笛卡尔积、选择、投影。交、连接、除可由基本运算表达。
- “三种常用专门运算”是选择、投影、连接，和“五种基本运算”是不同问题。

| 运算 | 含义 | 行列变化与限制 |
|---|---|---|
| 并 R∪S | 在 R 或 S 的元组，去重复 | 两关系要并相容 |
| 差 R−S | 在 R 不在 S | 并相容，不满足交换律 |
| 交 R∩S | 两者共有 | `R−(R−S)` |
| 笛卡尔积 R×S | 每个 R 元组配每个 S 元组 | 行数相乘、列数相加 |
| 选择 σ | 按条件筛选行 | 列数不变，行数不增加 |
| 投影 π | 挑选列并按理论关系去重 | 列数通常减少，行数可能减少 |
| θ 连接 | 笛卡尔积后按比较条件筛选 | 可为等值或非等值 |
| 自然连接 | 同名属性等值连接后合并重复列 | 列数=两者列数之和−公共列数 |
| 除法【延伸】 | 寻找满足“全部关联要求”的对象 | 如选修全部指定课程的学生 |

- 并相容：属性数量相同、对应域兼容，不能把任何两个表随意并起来。
- R 有 m 行 a 列，S 有 n 行 b 列，R×S 有 mn 行、a+b 列。
- R(A,B,C,D) 与 S(B,C,D) 自然连接结果为 **4 列**，不是 7 列；行数由实际匹配数据决定。
- `σ_{年龄>22且性别='男'}(学生)` 先筛行，再 `π_{学号,姓名}` 选列。
- **投影不是 SQL 中任意一个 SELECT 的完整同义词**；SQL SELECT 默认可保留重复，需要 DISTINCT 才与去重投影更接近。

## 8.5 数据库设计与三级模式

- 一般设计过程【补充完整框架】：需求分析→概念设计→逻辑设计→物理设计→实施→运行维护。
- 概念设计：先局部 E-R 图，综合为初步全局图，消除冲突与冗余，优化为基本 E-R 图；常用自底向上，也有自顶向下、逐步扩张、混合策略。
- 冲突：属性冲突（类型／范围／单位不同）、命名冲突（同名异义、异名同义）、结构冲突（实体／属性抽象不同、联系类型不同）。
- 逻辑设计：转换到选定 DBMS 支持的模型，形成关系模式、规范化、评价修正。
- E-R 转关系：实体变表；1:n 常在 n 端加入 1 端主键作外键和联系属性；m:n 新建联系表，包含两端键和联系属性；1:1 可选择一端纳入对方键并约束唯一，或单独建表。
- 本书把每种联系都先转换为一个关系再合并，是一种转换路线；不能据此说“每个 1:n 联系都必须永久多一张表”。
- 三级模式：外模式是用户视图，模式是全局逻辑结构，内模式是物理存储结构。
- 物理独立性：改变存储组织尽量不改逻辑结构与应用；逻辑独立性：逻辑结构变化时尽量保持用户视图与应用稳定。
- **规范化【延伸】**：1NF 属性原子；2NF 消除对候选键的部分依赖；3NF 进一步消除不合适的传递依赖；其目的包括减少更新、插入、删除异常。考试若仅限本书，优先掌握键、E-R 和 SQL。

## 8.6 SQL 分类、类型与建表

- SQL：Structured Query Language，结构化查询语言，高度非过程化，重在表达“要什么”；可交互使用或嵌入程序。
- DDL 数据定义：CREATE、ALTER、DROP；DML 数据操纵：INSERT、UPDATE、DELETE；SELECT 常单列为查询 DQL，也可归入广义 DML；DCL 数据控制：GRANT、REVOKE。
- 类型：INTEGER/INT、SMALLINT、DECIMAL(p,s)、FLOAT、CHAR(n)、VARCHAR(n)、DATE、TIME 等。p 是总精度、s 是小数位；`DECIMAL(3,1)` 最大正值 99.9，无法表示 100.0，成绩可考虑 `DECIMAL(5,2)`。
- CHAR 定长、VARCHAR 变长；不同 DBMS 中 n 表示字符数还是字节数等细节可能不同。学号、身份证等编号通常使用字符类型。
- 关键字不区分大小写的使用很常见，字符串值是否区分依排序规则；字符串一般用英文单引号，日期字面量规则依产品。

```sql
CREATE TABLE Student (
    Sno   VARCHAR(8) PRIMARY KEY,
    Sname VARCHAR(30) NOT NULL,
    Sex   CHAR(2),
    Age   INTEGER CHECK (Age BETWEEN 0 AND 150),
    Dept  VARCHAR(30)
);

CREATE TABLE Course (
    Cno    VARCHAR(8) PRIMARY KEY,
    Cname  VARCHAR(60) NOT NULL,
    Credit INTEGER
);

CREATE TABLE SC (
    Sno   VARCHAR(8),
    Cno   VARCHAR(8),
    Grade DECIMAL(5,2) CHECK (Grade BETWEEN 0 AND 100),
    PRIMARY KEY (Sno, Cno),
    FOREIGN KEY (Sno) REFERENCES Student(Sno),
    FOREIGN KEY (Cno) REFERENCES Course(Cno)
);
```

- 联合主键需按表级约束列出；不能把两个字段各自写成 PRIMARY KEY。
- 外键先建被参照表再建参照表；参照字段类型应兼容。
- `ALTER TABLE Student ADD Email VARCHAR(100);` 增字段。
- 修改字段类型语法依产品不同，如 SQL Server `ALTER COLUMN`、MySQL `MODIFY`、PostgreSQL `ALTER COLUMN ... TYPE`；不把不同方言拼在一个语句中。
- `DROP TABLE` 删除表定义及数据；被外键／视图等依赖时可能报错或需要显式处理依赖，不一定自动删除所有依赖。

## 8.7 SELECT 查询框架与条件

```sql
SELECT [DISTINCT] 字段或表达式
FROM 数据源
WHERE 行条件
GROUP BY 分组字段
HAVING 组条件
ORDER BY 排序字段 ASC或DESC;
```

书写顺序如上；可用 **FROM/JOIN→WHERE→GROUP BY→HAVING→SELECT→DISTINCT→ORDER BY** 理解逻辑处理，不等于数据库实际执行计划一定逐步如此。

- `SELECT *` 是选全部列，不等于绕过 WHERE 选择所有行；ALL 为保留重复的默认语义，DISTINCT 对整个结果列组合去重。
- 列表用逗号；别名可用 AS；表达式如 `Grade+5 AS NewGrade` 不会直接改原表数据。
- 比较 `= <> > >= < <=`；AND 优先于 OR，NOT 优先于 AND；复杂条件最好加括号。
- BETWEEN a AND b 包含边界；IN 是集合成员判断；LIKE `%` 匹配任意长度，`_` 匹配一个字符。
- 查姓刘：`Sname LIKE '刘%'`；两个字的刘姓姓名：`Sname LIKE '刘_'`。
- 标准 SQL 的 `%/_` 与 Windows/Excel 的 `*/?` 不同；某些 Access 模式使用 `*/?`，先看题目环境。
- 判断空值用 `IS NULL`／`IS NOT NULL`，不能用 `= NULL` 或 `<> NULL`。

```sql
SELECT Sno, Sname
FROM Student
WHERE Sex = '男' AND Age > 22;

SELECT DISTINCT Sno
FROM SC
WHERE Cno IN ('C1', 'C2') AND Grade >= 80;

SELECT Sno, Cno
FROM SC
WHERE Grade IS NULL;
```

## 8.8 聚合、分组和排序

- COUNT(*) 数行，包含某些列为 NULL 的行；COUNT(列) 数非 NULL 值；COUNT(DISTINCT 列) 数不同的非 NULL 值。
- SUM、AVG、MAX、MIN 通常忽略 NULL。AVG 不会把未录入成绩当 0，除非事先按要求转换。
- WHERE 筛选分组之前的行；HAVING 筛选分组后的组。不能在同一查询层的 WHERE 直接写 `AVG(Grade)>80`。
- SELECT 非聚合列通常应出现在 GROUP BY 中；不能一边按课程分组，一边随意选择学生姓名。
- ORDER BY 默认 ASC 升序，DESC 降序；多字段排序按书写先后比较。**未写 ORDER BY 不保证输出顺序**。

```sql
-- 各课程已录入成绩的人数、平均分
SELECT Cno, COUNT(Grade) AS N, AVG(Grade) AS AvgGrade
FROM SC
GROUP BY Cno;

-- 选课记录数超过 20 的课程
SELECT Cno, COUNT(*) AS N
FROM SC
GROUP BY Cno
HAVING COUNT(*) > 20;

-- 各系升序，同系年龄降序
SELECT * FROM Student
ORDER BY Dept ASC, Age DESC;
```

**【纠错】COUNT 不需要“一般都加 DISTINCT”，看计数对象；HAVING 也不在所有 SQL 实现中都必须与显式 GROUP BY 一起出现。**

## 8.9 连接、嵌套查询与集合查询

- 多表查询先找关联键，再写字段和筛选条件；漏连接条件可能产生笛卡尔积。
- 同名列需用表名／别名限定；连接列**不必同名**，但应有可比较的类型与符合业务的关联意义。
- 内连接保留匹配项；左连接保留左侧所有行，右侧不匹配列为 NULL；自身连接为同表起不同别名。

```sql
SELECT s.Sno, s.Sname, c.Cname, sc.Grade
FROM Student AS s
JOIN SC AS sc ON s.Sno = sc.Sno
JOIN Course AS c ON c.Cno = sc.Cno
WHERE c.Cname = '计算机基础' AND sc.Grade >= 85;
```

- 子查询可在 WHERE 等位置使用。标量子查询须至多得到单个值；多值通常用 IN、ANY、ALL 等方式处理。
- 不相关子查询不引用外查询当前行；相关子查询引用外层列，逻辑上随外层候选行判断，实际优化执行方式由 DBMS 决定。
- EXISTS 判断子查询是否存在至少一行；NOT EXISTS 判断无行，尤其适合“不存在符合条件的关联记录”。
- 在非空且无 NULL 的集合中：`> ANY` 等价于大于其最小值；`> ALL` 等价于大于其最大值。空集和 NULL 需另按 SQL 逻辑处理。
- **NOT IN 若子查询含 NULL，可能产生未知值，导致结果与直觉不同**，排除记录常优先考虑 NOT EXISTS。

```sql
-- 没有选 C2 的学生，包括完全未选课者
SELECT s.Sno, s.Sname
FROM Student AS s
WHERE NOT EXISTS (
    SELECT 1 FROM SC AS sc
    WHERE sc.Sno = s.Sno AND sc.Cno = 'C2'
);
```

`SELECT Sno FROM SC WHERE Cno <> 'C2'` 只能找“有非 C2 选课记录的人”，其中可能包含也选了 C2 的人，且漏掉完全未选课者。

- UNION 合并并去重，UNION ALL 保留重复；INTERSECT 求交；EXCEPT 求差，Oracle 常用 MINUS；各数据库支持程度有差异。
- 集合查询要求列数相同、对应类型可兼容，不一定要字段名、字段宽度完全相同。
- 教材把“所有子查询都禁止 ORDER BY”等写成通则不严谨：带 LIMIT／TOP／FETCH 等具体语法时另有规则；外层最终顺序仍需外层 ORDER BY。

## 8.10 INSERT、UPDATE、DELETE

```sql
INSERT INTO Student (Sno, Sname, Sex, Age, Dept)
VALUES ('S08', '赵普', '男', 20, '数学');

UPDATE SC
SET Grade = Grade + 5
WHERE Cno = 'C1' AND Grade <= 95;

DELETE FROM SC
WHERE Sno = 'S08';
```

- INSERT 明确列名可避免列序错误；字符串加引号，NULL 不加引号。
- 未指定的列可能取默认值、NULL、自动生成值，或因约束报错；不是统一取空值。
- `INSERT INTO 目标表(列...) SELECT ...` 可插入查询结果，目标列数与类型需匹配。
- UPDATE 无 WHERE 修改全部行；DELETE 无 WHERE 删除全部行，但通常保留表结构；DROP TABLE 删除表；TRUNCATE 为额外清空方式，权限、事务和外键行为依 DBMS。
- 关系表没有应依赖的自然“最后一行”；INSERT 不保证随后 SELECT 按插入次序输出。
- 删除父表记录时先处理子表外键引用，或使用已定义的级联规则；不能随便先删父表。
- 对多个相关表的修改最好放在事务中，全部成功后提交，失败回滚【延伸】。

## 8.11 视图、权限与事务补充

- 普通视图是查询定义形成的虚拟表，通常保存定义而不是一份独立持久结果；物化视图是另一类对象。
- 视图可限制可见行列、封装复杂查询、提供统一接口；权限配置正确时有助于数据保护，但不是绝对安全保证。
- 可在视图上查询、嵌套定义；是否可更新取决于能否明确映射到基本表与 DBMS 规则，含聚合、分组等视图通常不直接更新。

```sql
CREATE VIEW MathStudent AS
SELECT Sno, Sname, Sex, Age, Dept
FROM Student
WHERE Dept = '数学'
WITH CHECK OPTION;

SELECT Sno, Sname FROM MathStudent WHERE Age < 19;
DROP VIEW MathStudent;
```

- WITH CHECK OPTION 检查经视图插入／更新后的行是否仍满足视图条件，**不自动替用户给缺省字段填上筛选常量**。
- DROP VIEW 通常只删视图定义，不删原表数据；依赖视图的处理按数据库规则。
- `GRANT SELECT ON Student TO user1;` 授权；`REVOKE SELECT ON Student FROM user1;` 收回权限。用户创建、标识符、授权细节依具体 DBMS。
- **事务 ACID【延伸】**：原子性、一致性、隔离性、持久性；COMMIT 提交，ROLLBACK 回滚。备份恢复、日志和并发控制支撑系统可靠运行。

**本章自检**：能否根据业务找主外键和联系类型？能否算笛卡尔积／自然连接列数？能否写分组查询、三表连接和“未选某课”查询？能否区分 WHERE/HAVING、COUNT(*)/COUNT(列)、DELETE/DROP、DB/DBMS/DBS？

---

[系列目录与阅读说明](/posts/computer-review/00-overview/) · [上一篇：07｜多媒体技术与信息安全](/posts/computer-review/07-multimedia/)
