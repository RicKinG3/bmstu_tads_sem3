#ifndef __MENU_H__
#define __MENU_H__

#include "mtr.h"
#include "mtr_struct.h"

#define MAX_MENU_ITEM_LEN 128

void print_menu(void);
void print_info(void);

int choose_action(int *action);

int do_action(int action,
              sparse_mtr_t *sparse_mtr,
              sparse_mtr_t *sparse_row,
              mtr_t *mtr,
              mtr_t *row);
void print_error_message(int code);

#endif