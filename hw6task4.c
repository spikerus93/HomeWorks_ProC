/*
Задание 4. Удаление элементов

Напишите программу, которая удаляет из списка все элементы с нечетным порядковым номером.

Пример №1
Данные на входе: aa ss dd ff gg hh jj kk ll.
Данные на выходе: aa dd gg jj ll

Пример №2
Данные на входе: aa ss dd ff gg hh jj kk ll tt.
Данные на выходе: aa dd gg jj ll
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_SIZE 2000

typedef struct list
{
    char *word;
    struct list *next;
} list;

list *insert_to2(char *value, list *head);

void print_list(list *head);
void delete_list(list *head);
void print_elements(list *element);

void delete_list(list *l)
{
    list *c = l;
    list *n;

    while (c != NULL)
    {
        n = c->next;
        free(c->word);
        free(c);
        c = n;
    }
}

list *insert_to2(char *value, list *head)
{
    list *new = calloc(1, sizeof(list));
    int len = strlen(value);
    new->word = malloc(len++);
    strcpy(new->word, value);

    if (head == NULL)
        return new;
    else
    {
        list *p = head;

        while (p->next != NULL)
            p = p->next;
        p->next = new;
        return head;
    }
}

void print_list(list *head)
{
    for (list *i = head; i != NULL; i = i->next)
        printf("%s ", i->word);
    putchar('\n');
}

void print_elements(list *element)
{
    int i = 0;
    struct list *l = element;

    while (l != NULL)
    {
        if ((i % 2) == 0)
            printf("%s ", l->word);
        l = l->next;
        i++;
    }
}

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
            w_list = insert_to2(word, w_list);
            i = 0;
            break;
        default:
            word[i++] = ch;
            if (i >= STR_SIZE)
                i = 0;
        }
        if ('.' == ch)
            break;
    }
#ifdef DEBUG
    print_list(w_list);
#endif

    print_elements(w_list);
    delete_list(w_list);

    return 0;
}