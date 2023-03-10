#ifndef __IO_H__
#define __IO_H__

#include <stdlib.h>
#include <stdio.h>
#include "tree_node.h"

int read_line(FILE *f, char **const str);
int read_f_in_bin_tree_ex(FILE *f, tree_node_t **root);
int generate_gv(tree_node_t *root);
int read_int(void);
size_t read_line_action(char *s, size_t n, FILE *f);
char *read_str_in_stdin(void);
void printf_tree_and_gener_gv(tree_node_t * root);
int generate_gv_ex(tree_node_t *root, char *name_f);

#endif
