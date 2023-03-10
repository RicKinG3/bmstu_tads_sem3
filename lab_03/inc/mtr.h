#ifndef __mtr_H__

#define __mtr_H__

#include "func.h"
#include "mtr_struct.h"
#include <math.h>
#define EPS 1e-5

size_t read_line(char *s, size_t n, FILE *f);

int read_row(mtr_t *row, sparse_mtr_t *sparse_row, int columns_num);

int mtr_init(mtr_t *mtr, int rows, int columns, int nonzeros_num);

void free_mtr_t(mtr_t *mtr);

int **allocate_mtr(int n, int m);

void free_mtr(int **data, int n);

int sparse_mtr_init(sparse_mtr_t *mtr,
                    int rows, int columns, int nonzero_num);

void create_mtr_by_sparse(sparse_mtr_t *sparse_mtr, mtr_t *mtr);

int user_print(mtr_t *mtr, mtr_t *row,
               sparse_mtr_t *sparse_mtr, sparse_mtr_t *sparse_row);
int read_mtr_elements(sparse_mtr_t *sparse_mtr, mtr_t *mtr,
                      int nonzeros);

int read_row_elements(sparse_mtr_t *sparse_row, mtr_t *row,
                      int nonzeros);
int read_mtres(sparse_mtr_t *sparse_mtr, sparse_mtr_t *sparse_row,
               mtr_t *mtr, mtr_t *row);

int read_mtr(mtr_t *mtr, sparse_mtr_t *sparse_mtr,
             int *rows_num, int *columns_num);
void free_sparse_t(sparse_mtr_t *sparse_mtr);
void create_sparse_by_mtr(mtr_t *mtr, sparse_mtr_t *sparse_mtr);

int print_mtr(mtr_t *mtr);

int print_sparse(sparse_mtr_t *mtr);

void generate_mtr(mtr_t *mtr, sparse_mtr_t *sparse_mtr);

int generate_mtres(sparse_mtr_t *sparse_mtr, sparse_mtr_t *sparse_row,
                   mtr_t *mtr, mtr_t *row);

#endif