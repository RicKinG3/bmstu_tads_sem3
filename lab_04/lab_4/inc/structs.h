#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include <stdio.h>

#define MAX_STACK 1001
typedef struct arr
{
    int *arr; //указатель на текущий элемент стека
    int len; //количество элементов в стеке
} arr_t;

typedef struct list
{
    int ind; //номер элемента в стеке
    int num; //значение текущего элемента в стеке

    struct list *next; //указатель на следующий элемент стека
} list_t;

typedef struct
{
    char sym[MAX_STACK]; //выражение 
    int len; //кол-во символов
    
} expres_t;

typedef struct
{
    list_t *arr_clear[1000];
    int len;
} arr_clear_t;

#endif