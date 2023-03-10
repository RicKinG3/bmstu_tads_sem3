#ifndef __mtrES_ACTIONS_H__

#define __mtrES_ACTIONS_H__

#include "mtr.h"
#include "mtr_struct.h"


int sparse_multiply_row_and_mtr(sparse_mtr_t *row, sparse_mtr_t *mtr, int mode, int *time);

int multiply_row_and_mtr(mtr_t *row, mtr_t *mtr, int mode, int *time);
void print_table_measure(sparse_mtr_t *row, sparse_mtr_t *mtr, mtr_t *rw, mtr_t *mr);

int choice_print(mtr_t *mtr, sparse_mtr_t *sparse_mtr);

#endif