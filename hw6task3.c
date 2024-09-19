/*
Задание 3. Разница между элементами

Напишите программу, которая находит разницу между максимальным и минимальным элементом в дереве.*/

#include <stdio.h>

#define data int

typedef struct tree
{
    data key;
    struct tree *left, *right, *parent;
} tree;

void max_min(tree *root, tree *element)
{
    static int min = 10000;
    static int max = 0;

    if (root == NULL)
        return;
    max = min < root->key ? root->key : max;
    min = min > root->key ? root->key : min;

    if (root->left)
        max_min(root->left, element);
    if (root->right)
        max_min(root->right, element);
    if (element == root)
        printf("%d", max - min);
}

int main()
{
    tree t[10] = {0, 0, 0, 0};

    t[0].left = t + 1;
    t[0].right = t + 2;
    t[0].key = 10;

    t[1].left = t + 3;
    t[1].right = t + 4;
    t[1].key = 5;
    t[1].parent = t + 0;

    t[2].left = t + 7;
    t[2].right = t + 6;
    t[2].key = 15;
    t[2].parent = t + 0;

    t[3].left = t + 7;
    t[3].parent = t + 1;
    t[3].key = 3;

    t[4].left = t + 8;
    t[4].parent = t + 1;
    t[4].key = 7;

    t[5].key = 13;
    t[5].parent = t + 2;

    t[6].key = 18;
    t[6].parent = t + 2;

    t[7].key = 1;
    t[7].parent = t + 3;

    t[8].key = 6;
    t[8].parent = t + 4;

    max_min(t, t);

    return 0;
}