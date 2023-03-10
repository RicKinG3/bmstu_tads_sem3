#ifndef __RW_STUDENT_H__
#define __RW_STUDENT_H__

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "../inc/struct_inf_stdnt.h"

#define LOUD_INPUT 1
#define QUIT_INPUT 0
#define START 0
void print_menu(void);
void input_key_tables(inf_stdnt_t *arr_stdnt, key_tables_t *arr_key, int num_count_std);
void print_key_tables(key_tables_t *arr_key, int num_count_std);
void print_error_input(int rc);
int item_input(FILE *f, inf_stdnt_t *arr_stdnt, char *count_stdnt, int *num_count_std, int item);
size_t read_line(char *s, size_t n, FILE *f);
int input_stdnt(inf_stdnt_t *stdnt, int count_stdnt, FILE *f, int mode, int pos);
void print_stdnt(inf_stdnt_t *stdnt, key_tables_t *arr_key, int count_std, int mode);
void print_info(void);
void print_stnt_hostel_by_year(inf_stdnt_t *arr_stdnt, int count_std, int year);

#endif