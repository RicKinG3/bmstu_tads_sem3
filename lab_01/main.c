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
#define DOP_BUF 10 // for input more 30 simbol
#define P 5

int main(void)
{
    char int_number[LEN + DOP_BUF];
    char flt_number[LEN + DOP_BUF];
    int rc = 0;
    int error_code = PASS;
    number number_int;
    number number_flt;
    number result;

    puts("Format ± integer num ");
    puts("Enter an integer less than thirty numbers: ");
    if (fgets(int_number, LEN + DOP_BUF, stdin) == NULL)
    {
        puts("Error: input integer");
        return ERR_INPUT;
    }
    if (read_int(&number_int, int_number) != PASS)
    {
        puts("Error: input integer format or input incorect simbol");
        return ERR_INPUT;
    }

    puts("Enter an real number in format: ±m.n E ±K, where m+n total length <= thirty digits and K length <= five digits: ");
    if (fgets(flt_number, LEN + DOP_BUF, stdin) == NULL)
    {
        puts("Error: input real");
        return ERR_INPUT;
    }

    if (read_flt(&number_flt, flt_number) != PASS)
    {
        puts("Error: input real format or input incorect simbol");
        return ERR_INPUT;
    }

    rc = 2;
    if (rc == 2)
    {

        if (error_code == PASS)
            error_code = multiplication(&number_int, &number_flt, &result);
    }
    else
        error_code = ERR_INPUT;
    if (error_code == PASS)
        printf("%c0.%s E %d\n", result.sign, result.number, result.order);
    else if (error_code == ERR_INPUT)
        printf("Invalid Input\n");
    else if (error_code == DATA_ERROR)
        printf("Data Error\n");
    else if (error_code == ORDER_OVERFLOW)
        printf("Order Overflow\n");
    return error_code;
}