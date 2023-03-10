#ifndef __PARSING_H__
#define __PARSING_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "struct.h"
#include <stdbool.h>

#define PASS 0
#define RANGE_ERR 3
#define RANGE_ERR_MNT 4

#define MAX_DEGREE_CN 8
#define MAX_DEGREE_SZ 99999

bool null_check(number_t *num1, int len);

int add_degree_p(number_t num);
int final_parsing(number_t num1, number_t num2, number_t *result, bool fl);
int parsing_mantissa(char *num, number_t *num_parsed, int *ind);
int parsing_degree(char *num, number_t *num_parsed, int *ind, char *temp_degree, int len);
int parsing(char *num, number_t *num_parsed);

void null_counter(char *fin_mantissa, int len, int *null_cnt, bool back_flag);
void find_degree(number_t *result, int ind);
void std_data(number_t *num_parsed);
void sign_check(char *num, number_t *num_parsed, int *ind);

#endif