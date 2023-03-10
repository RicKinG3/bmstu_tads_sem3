#ifndef __MENU_IO_H__
#define __MENU_IO_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_MENU_ITEM_LEN 128

void print_menu(void);
void print_info(void);
void print_error_message(int code);
int read_action_bim(void);

int choose_action(int *action);

#endif
