---
title: "计算机复习 · 附录 A｜程序设计实操"
published: 2026-09-21
description: "围绕数组插入、字母金字塔、最大值、冒泡排序与循环累加，补齐综合题需要的编程能力。"
tags: ["计算机复习","程序设计","算法"]
category: 计算机复习
lang: zh_CN
draft: false
---

> 本文属于「计算机复习」系列。[系列目录与阅读说明](/posts/computer-review/00-overview/)；文中页码指原教材 PDF 页码，Windows／Office 操作沿用 Windows 7／Office 2010 语境。

**来源：第 232 页、第 241 页、第 247 页程序设计选做题。** 第一章讲了语言与算法概念，但缺少足够的编码训练。下列用 Python 3 展示算法，便于理解；标明语言不限的题可参考，具体考试若指定语言，应按指定语法作答。随机插入题原页未单独注明语言限制，此处仅用 Python 演示思路。

## A.1 编程前置知识

- 变量保存数据；整数、实数、字符串、布尔值用途不同；输入通常先是字符串，需要数值转换。
- 赋值 `=` 与比较 `==` 不同；Python `and/or/not` 与 C 的 `&&/||/!` 对应逻辑运算，不是按位运算。
- `for`／`while` 要包含初始化、条件、更新，防止死循环；Python `range(a,b)` 包含 a 不含 b。
- 顺序表／数组下标通常从 0 开始，n 个元素最大下标为 n−1；插入需要移动元素，查找要考虑“没有找到”。
- 求和初值 0，求积初值 1，计数初值 0；求最大值通常用第一个有效元素初始化，不能任意写 0，否则全负数可能算错。
- 测试边界：空／最短数据、全部相等、负数、最大最小值、插在头尾、已经有序、重复值。
- 时间复杂度【延伸】：顺序扫描 O(n)，冒泡排序最坏 O(n²)，二分查找 O(log n) 且前提为有序；复杂度不是精确秒数。

## A.2 原书第 232 页：降序数组中插入一个随机整数

原数组为 `[38,29,25,18,17,12,9,6,4]`，随机数范围为 **0—40**。关键在于保持“降序”，不能套升序判断。

```python
import random

def insert_desc(values, x):
    a = values[:]             # 复制数据，便于比较插入前后
    a.append(0)              # 新增一个空间
    j = len(a) - 2
    while j >= 0 and a[j] < x:
        a[j + 1] = a[j]      # 比 x 小的元素右移
        j -= 1
    a[j + 1] = x
    return a

a = [38, 29, 25, 18, 17, 12, 9, 6, 4]
x = random.randint(0, 40)     # 两端都包含
print(x)
print(insert_desc(a, x))
```

应会解释：x=40 插开头，x=0 插末尾，x=25 仍保持非递增。算法最多移动原数组全部元素，时间 O(n)。考插入过程时不要仅用 `sort()` 掩盖核心算法。

## A.3 原书第 232 页：字母金字塔

第 i 行有 `6−i` 个前导空格、`2i−1` 个字母，字母依次 A—F。此处按等宽字符排版。

```python
def letter_pyramid(n=6):
    lines = []
    for i in range(1, n + 1):
        ch = chr(ord('A') + i - 1)
        lines.append(' ' * (n - i) + ch * (2 * i - 1))
    return lines

for line in letter_pyramid():
    print(line)
```

```text
     A
    BBB
   CCCCC
  DDDDDDD
 EEEEEEEEE
FFFFFFFFFFF
```

扩展到 C 语言时，外层循环控制行数，两个内层循环分别输出空格与字母，每行结束输出换行。

## A.4 原书第 241 页：三个整数求最大值

```python
def max_of_three(a, b, c):
    m = a
    if b > m:
        m = b
    if c > m:
        m = c
    return m

a, b, c = map(int, input().split())
print(max_of_three(a, b, c))
```

两个判断不能误写成只能执行一次比较的 `if…elif` 结构；例如 1、2、3，比较 b 后还必须比较 c。若题目只要求结果可用 max，但用显式比较更能展示选择结构。

## A.5 原书第 241 页：10 个整数冒泡升序排序

```python
def bubble_sort(values):
    a = values[:]
    n = len(a)
    for end in range(n - 1, 0, -1):
        changed = False
        for j in range(end):
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                changed = True
        if not changed:
            break
    return a

a = list(map(int, input().split()))
if len(a) != 10:
    raise ValueError('请按题目要求输入 10 个整数')
print(*bubble_sort(a))
```

每趟把当前未排序部分的最大数交换到末尾；最多 9 趟，最坏比较 10×9÷2=45 次。`j+1` 不能越界；只有发现前项大于后项才交换。

## A.6 原书第 247 页：1 加到 100

```python
def sum_to(n):
    total = 0
    for i in range(1, n + 1):
        total += i
    return total

print(sum_to(100))            # 5050
```

循环终点要包括 100。可以用等差数列公式 n(n+1)/2 验算；若题目要求循环，不仅写现成求和函数。

## A.7 可能出现的同类延伸题

以下为推演的训练方向，**不表示这份 PDF 已考过，更不是押题承诺**：

- 求最大最小、平均值、合格人数：扫描+条件+累加／计数。
- 求阶乘：乘积初值为 1，0!=1；大 n 考虑溢出。
- 判断素数：n≥2，试除至平方根；1 不是素数。
- 最大公约数：辗转相除；最小公倍数可用 `a/gcd(a,b)×b`。
- 数字拆位：整除 10 与模 10；回文数、水仙花数是常见应用。
- 有序数组查找：顺序查找、二分查找；插入排序与冒泡排序不要混淆。
- 字符／图案题：行号、空格数、字符数先列规律，再写循环。

---

[系列目录与阅读说明](/posts/computer-review/00-overview/) · [上一篇：08｜数据库技术基础](/posts/computer-review/08-databases/) · [下一篇：附录 B｜数据库综合题](/posts/computer-review/10-database-exercises/)
