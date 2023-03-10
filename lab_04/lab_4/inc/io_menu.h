#ifndef __PRINT_MENU_H__
#define __PRINT_MENU_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_MENU_ITEM_LEN 128
#define PASS 0
#define ERR_READ_ACTION 1
#define ERR_STR_READ 2
#define ERR_WRONG_ACTION 3

void print_info(void);

void flush_input(void);
void print_menu(void);
size_t read_line(char *s, size_t n, FILE *f);
bool check_int(char *num);
int input_int(int *num);
int input_max_len_stack(int *max_len);
int choose_action(int *action);

#endif