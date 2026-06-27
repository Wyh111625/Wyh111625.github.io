# 单链表常见题目整理

这篇笔记整理几个单链表常见题型：快慢指针、找两个链表的公共后缀、按绝对值去重、反转链表、删除中间结点、判断是否有环。

链表题最重要的不是背代码，而是看清楚两个问题：

1. 当前结点是谁。
2. 如果要删除或反转，前后结点的连接关系怎么改。

## 基本结点结构

普通单链表结点可以写成：

```c
typedef struct Node
{
    int data;
    struct Node *next;
} Node;
```

如果题目使用的是带头结点的链表，`head` 本身不存有效数据，第一个真正的数据结点是：

```c
head->next
```

如果是不带头结点的链表，`head` 就直接指向第一个数据结点。

## 一、快慢指针

快慢指针就是设置两个指针：

```c
Node *slow = head;
Node *fast = head;
```

然后让它们以不同速度移动：

```c
slow = slow->next;
fast = fast->next->next;
```

`slow` 一次走一步，`fast` 一次走两步。

### 1. 找链表中间结点

题目：给定一个不带头结点的单链表，返回中间结点。

```c
Node *findMiddle(Node *head)
{
    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
```

例如：

```text
10 -> 20 -> 30 -> 40 -> 50
```

移动过程：

```text
slow: 10 -> 20 -> 30
fast: 10 -> 30 -> 50
```

当 `fast` 到达尾部时，`slow` 正好在中间。

### 2. 判断链表是否有环

如果链表无环，`fast` 最终会走到 `NULL`。

如果链表有环，`fast` 会在环中追上 `slow`。

```c
int hasCycle(Node *head)
{
    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            return 1;
        }
    }

    return 0;
}
```

重点：

```c
while (fast != NULL && fast->next != NULL)
```

因为 `fast` 一次走两步，所以必须先判断 `fast` 和 `fast->next` 都不为空。

## 二、删除链表中间结点

题目：删除不带头结点单链表的中间结点。

思路：

1. 用 `slow` 找中间结点。
2. 用 `fast` 帮 `slow` 定位。
3. 用 `pre` 保存 `slow` 的前一个结点，方便删除。

```c
Node *deleteMiddle(Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }

    if (head->next == NULL)
    {
        free(head);
        return NULL;
    }

    Node *slow = head;
    Node *fast = head;
    Node *pre = NULL;

    while (fast != NULL && fast->next != NULL)
    {
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    pre->next = slow->next;
    free(slow);

    return head;
}
```

为什么需要 `pre`？

因为单链表删除一个结点时，必须让它前面的结点跳过它。

```text
10 -> 20 -> 30 -> 40
      ^     ^
     pre   slow
```

删除 `30`：

```c
pre->next = slow->next;
```

这样 `20` 就直接指向 `40`。

## 三、反转链表

题目：反转不带头结点的单链表。

反转前：

```text
10 -> 20 -> 30 -> NULL
```

反转后：

```text
30 -> 20 -> 10 -> NULL
```

核心指针：

```c
Node *prev = NULL;
Node *cur = head;
Node *next = NULL;
```

代码：

```c
Node *reverseList(Node *head)
{
    Node *prev = NULL;
    Node *cur = head;
    Node *next = NULL;

    while (cur != NULL)
    {
        next = cur->next;
        cur->next = prev;

        prev = cur;
        cur = next;
    }

    return prev;
}
```

最关键的两句：

```c
next = cur->next;
cur->next = prev;
```

先保存后面的结点，再把当前结点的箭头反过来。

如果先写：

```c
cur->next = prev;
```

后面的链表就可能找不到了。

## 四、找倒数第 k 个结点

这也是双指针思想。

思路：

1. `fast` 先走 `k` 步。
2. 然后 `slow` 和 `fast` 一起走。
3. 当 `fast` 到达 `NULL` 时，`slow` 指向倒数第 `k` 个结点。

```c
Node *findKthFromEnd(Node *head, int k)
{
    Node *fast = head;
    Node *slow = head;

    for (int i = 0; i < k; i++)
    {
        if (fast == NULL)
        {
            return NULL;
        }

        fast = fast->next;
    }

    while (fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }

    return slow;
}
```

这种写法让 `fast` 和 `slow` 始终保持 `k` 个结点的距离。

## 五、找两个链表公共后缀的起点

题目：用带头结点的单链表保存单词，如果两个单词有相同后缀，则共享相同后缀的存储空间。求公共后缀的起始结点。

例如：

```text
str1: head -> l -> o -> a -> d \
                              i -> n -> g -> NULL
str2: head -> b -> e ---------/
```

公共后缀起点是字符 `i` 所在结点。

注意：这里判断公共后缀不能比较 `data`，而要比较地址。

错误写法：

```c
if (p1->data == p2->data)
```

正确写法：

```c
if (p1 == p2)
```

因为公共后缀表示两个链表从某个位置开始共享同一批结点。

### 算法思想

1. 分别求两个链表长度。
2. 长链表先走长度差。
3. 两个指针一起走。
4. 第一次地址相同的位置就是公共后缀起点。

字符链表结点：

```c
typedef struct CharNode
{
    char data;
    struct CharNode *next;
} CharNode;
```

代码：

```c
int getCharListLength(CharNode *head)
{
    int len = 0;
    CharNode *p = head->next;

    while (p != NULL)
    {
        len++;
        p = p->next;
    }

    return len;
}

CharNode *findCommonSuffixStart(CharNode *str1, CharNode *str2)
{
    int len1 = getCharListLength(str1);
    int len2 = getCharListLength(str2);

    CharNode *p1 = str1->next;
    CharNode *p2 = str2->next;

    while (len1 > len2)
    {
        p1 = p1->next;
        len1--;
    }

    while (len2 > len1)
    {
        p2 = p2->next;
        len2--;
    }

    while (p1 != NULL && p2 != NULL)
    {
        if (p1 == p2)
        {
            return p1;
        }

        p1 = p1->next;
        p2 = p2->next;
    }

    return NULL;
}
```

时间复杂度：

```text
O(m + n)
```

空间复杂度：

```text
O(1)
```

## 六、删除绝对值重复的结点

题目：用单链表保存 `n` 个整数，结点结构为：

```text
data | link
```

并且：

```text
|data| < n
```

对于链表中 `data` 的绝对值相等的结点，只保留第一次出现的结点，删除其余结点。

例如：

```text
head -> 21 -> -15 -> -15 -> -7 -> 15 -> NULL
```

看绝对值：

```text
21, 15, 15, 7, 15
```

删除后：

```text
head -> 21 -> -15 -> -7 -> NULL
```

### flag 是什么

`flag` 是一个数组，用来记录某个绝对值是否已经出现过。

```c
flag[15] == 0
```

表示绝对值 `15` 还没出现过。

```c
flag[15] == 1
```

表示绝对值 `15` 已经出现过。

遇到 `-15` 时：

```c
int x = abs(-15);
```

得到：

```text
x = 15
```

如果 `flag[15] == 0`，说明第一次出现，保留。

如果 `flag[15] == 1`，说明之前出现过，删除。

### pre 是什么

`pre` 指向当前结点 `p` 的前一个结点。

```text
pre    p
 |     |
 v     v
21 -> -15 -> -7
```

删除 `p` 时，要让 `pre` 直接指向 `p` 的下一个结点：

```c
pre->next = p->next;
```

这样就跳过了 `p`。

### 代码

```c
void deleteSameAbs(Node *head, int n)
{
    int *flag = (int *)calloc(n, sizeof(int));

    if (flag == NULL)
    {
        return;
    }

    Node *pre = head;
    Node *p = head->next;

    while (p != NULL)
    {
        int x = abs(p->data);

        if (flag[x] == 0)
        {
            flag[x] = 1;
            pre = p;
            p = p->next;
        }
        else
        {
            Node *temp = p;
            pre->next = p->next;
            p = p->next;
            free(temp);
        }
    }

    free(flag);
}
```

保留当前结点：

```c
pre = p;
p = p->next;
```

删除当前结点：

```c
pre->next = p->next;
p = p->next;
```

区别是：删除时 `pre` 不动，保留时 `pre` 才往后走。

时间复杂度：

```text
O(m)
```

其中 `m` 是链表结点个数。

空间复杂度：

```text
O(n)
```

因为用了一个大小为 `n` 的辅助数组。

## 总结

链表题常用套路：

1. 快慢指针：找中点、判断有环。
2. 前后指针：删除结点。
3. 三指针：反转链表。
4. 辅助数组：快速判断某个值是否出现过。
5. 地址比较：判断两个链表是否共享结点。

最容易错的地方：

1. 删除结点时忘记保存前驱结点。
2. 反转链表时没有先保存 `next`。
3. 带头结点和不带头结点混在一起。
4. 找公共后缀时比较了 `data`，而不是比较结点地址。
