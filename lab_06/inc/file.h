#ifndef __FILE_H__
#define __FILE_H__

#include <stdlib.h>
#include <stdio.h>

void add_word_in_f(FILE *f, char *input_word);
int find_word_file_ex(FILE *f, tree_node_t **root, char *input_word);
void print_file(FILE *f);

int find_word_file(FILE *f, char *input_word);
int del_word_in_file(FILE *f, char *input_word, char *name_file);

#endif
