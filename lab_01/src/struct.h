#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MANTISSA 31
#define MAX_DEGREE 6
#define OK 0
#define READ_ERROR 1
#define INVALID_DATA 2
#define RANGE_ERR 3
#define RANGE_ERR_MNT 4
#define NO_SIGN 5
#define NO_DEGREE_SIGN 6

typedef struct number
{
    char mantissa_sign; // знак мантиссы
    char mantissa[MAX_MANTISSA * 2]; // сама мантисса
    int degree; // степень
    int point_ind; // индекса нахождения точки
} number_t;

#endif