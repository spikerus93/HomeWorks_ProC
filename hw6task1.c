/*
Задание 1. Поиск первого и последнего слова

Используя код задачи 1, написать программу поиска первого и последнего слова в строке.

Пример №1
Данные на входе: efg abcd zzz.
Данные на выходе: efg zzz.

Пример №2
Данные на входе: fffff kkkkkk a.
Данные на выходе: fffff a.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_SIZE 2000

typedef struct list
{
    char *word;
    struct list *next;
} list;

list *insert2(char *value, list *head);

void print_list(list *head);
void choose_sort_array_list(list *head, char *firstWord, char *lastWord);
void swap_elements(list *el, list *e2);
void delete_list(list *head);

int main()
{
    list *w_list = NULL;
    char word[STR_SIZE] = "";
    int ch = ' ';
    int i = 0;

    while (EOF != (ch = getchar()))
    {
        switch (ch)
        {
        case '.':
        case ' ':
            word[i] = '\0';
            w_list = insert2(word, w_list);
            i = 0;
            break;
        default:
            word[i++] = ch;

            if (i >= STR_SIZE)
                i = 0; // Защита от переполнения строки
        }
        if ('.' == ch)
            break;
    }

#ifdef DEBUG
    print_list(w_list);
#endif

    print_list(w_list);

    delete_list(w_list);
    return 0;
}

void delete_list(list *l)
{
    list *c = l;
    list *n;

    while (c != NULL)
    {
        n = c->next;
        free(c->word); // Очищаем память под слово.
        free(c);
        c = n;
    }
}

// Без заглавного элемента и без двойного указателя
list *insert2(char *value, list *head)
{
    list *res = (list *)calloc(1, sizeof(list));
    int len = strlen(value);     // определить размер строки
    res->word = malloc(len + 1); // выделяем память
    strcpy(res->word, value);    // Копируем строку в память
    res->next = head;
    return res;
}

void swap_elements(list *e1, list *e2)
{
    char *tmp = e1->word; // просто смена указателя на строки
    e1->word = e2->word;
    e2->word = tmp;
}

void print_list(struct list *head)
{
    struct list *last = head;
    while (last->next != (struct list *)NULL)
        last = last->next;
    printf("%s ", last->word);
    printf("%s\n", head->word);
}