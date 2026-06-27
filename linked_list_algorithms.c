#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct CharNode
{
    char data;
    struct CharNode *next;
} CharNode;

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

Node *findKthFromEnd(Node *head, int k)
{
    if (k <= 0)
    {
        return NULL;
    }

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

int main(void)
{
    return 0;
}
