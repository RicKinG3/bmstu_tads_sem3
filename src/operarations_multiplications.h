
#ifndef __OPERRATIONS_MULTIPLICATIONS_H__
#define __OPERRATIONS_MULTIPLICATIONS_H__

#include "struct.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_DEGREE_SIZE 99999
#define SIGN_DEGREE 8

#define PASS 0
#define ERR_RANGE 3

void add_null(char *arr);
void add_null(char *arr);
void null_rounding(number_t *numb, size_t ind);
void disch_multp(char *num1, int len1, char *tmp, int tmp_len, int multp_num);
void disch_sum(char *res, char *tmp, int len);
void multp_mantissa(char *num1, int len1, char *num2, int len2, char *mantissa, int disch);
void normalize(number_t *num);
void point_defin(number_t *num1, number_t *num2, number_t *result);
void reduction_to_exp(char *num);
void sign_defin(number_t *num1, number_t *num2, number_t *result);
void rounding(number_t *numb, int end_ind, int flag);

bool check_exp(char *num, size_t cur_len, size_t len);

int multp(number_t *num1, number_t *num2, number_t *result);
int char_to_int(char symb);

#endif