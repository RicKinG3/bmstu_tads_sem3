#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "readme.h"
#include "operations.h"

#define PASS 0
#define ERR_INPUT 1
#define DATA_ERROR 2
#define ORDER_OVERFLOW 3

#define LEN 30
#define MAX_ORDER 99999

void fill_wth_zeroes(char *result_number);
void rounding(char *result_number);
void remove_zeroes(char *result_number, int *result_order);

int multiplication(number *number1, number *number2, number *result)
{
    int result_order = 0;
    int error_code = PASS;
    char result_number[2 * LEN + 1];
    fill_wth_zeroes(result_number);
    char result_sign;
    if (number1->sign == number2->sign)
        result_sign = '+';
    else
        result_sign = '-';
    if ((number1->number[0] == '0' && number1->after_dot_len == 0) || (number2->number[0] == '0' && number2->after_dot_len == 0))
    {
        result->order = 0;
        result->number[0] = '0';
        result->number[1] = '\0';
        result->sign = result_sign;
    }
    else
    {
        for (int i = 0; i < number1->len; i++)
        {
            for (int j = 0; j < number2->len; j++)
            {
                short int m = (number1->number[i] - '0') * (number2->number[j] - '0') + (result_number[i + j + 1] - '0');
                short int ost = m / 10;
                int k = -1;
                result_number[i + j + 1] = m % 10 + '0';
                while (ost)
                {
                    m = ost + (result_number[i + j + 1 + k] - '0');
                    ost  = m / 10;
                    result_number[i + j + k + 1] = m % 10 + '0';
                    k--;
                }
            }
        }
        remove_zeroes(result_number, &result_order);
        rounding(result_number);
        result_order += number1->order + number2->order;
        if (abs(result_order) > MAX_ORDER)
            error_code = ORDER_OVERFLOW;
        else
        { 
            strcpy(result->number, result_number);
            result->sign = result_sign;
            result->order = result_order;
        }
    }
    return error_code;
}

void fill_wth_zeroes(char *result_number)
{
    for (int i = 0; i < LEN * 2; i++)
        result_number[i] = '0';
    result_number[LEN * 2 + 1] = '\0';
}

void remove_zeroes(char *result_number, int *result_order)
{
    while (result_number[0] == '0')
    {
        for (int j = 0; j < LEN * 2; j++)
            result_number[j] = result_number[j + 1];
        result_number[LEN * 2] = '0';
        (*result_order)--;
    }
}

void rounding(char *result_number)
{
    for (int i = 1; i < LEN + 1; i++)
    {
        if (result_number[2 * LEN - i] >= '5')
            result_number[2 * LEN - i - 1]++;
        result_number[2 * LEN - i] = '\0';
    }
    int i = 1;
    for (; i < LEN && result_number[LEN - i] == '0'; i++)
        result_number[LEN - i] = '\0';
    for (; i < LEN && result_number[LEN - i] > '9'; i++)
    {
        result_number[LEN - i - 1]++;
        result_number[LEN - i] = '\0';
    }
}
