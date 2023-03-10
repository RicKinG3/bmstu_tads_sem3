#ifndef __DATA_CHECK_H__
#define __DATA_CHECK_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N_ALLOWED_SIG 5
#define MAX_E 1

#define PASS 0
#define INVALID_DATA 2
#define NO_SIGN 5
#define NO_DEGREE_SIGN 6

int check_allowed(char symb, int i, int not_allowed_cnt);
int is_sign_after_exp(char *num, size_t i);
int check_pos_sign_and_exp(char *num, size_t i);
int is_one_e(char symb, int *e_cnt);
int check_point_in_degree(char *num, size_t i, int *e_cnt);
int is_one_point(char *num, int i, int *point_cnt);
int check_num(char *num, size_t len, int *e_cnt);
int check_sign(char *num);
int check_real(char *num);
bool check_int(char *num);

#endif