#ifndef __BIN_TREE_H__

#define __BIN_TREE_H__

#include <stdio.h>
#include "tree_node.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 158
#include "../inc/hash.h"

int create_tree_avl(tree_node_t **root, FILE *f_in);

void delete_word(tree_node_t **tree, char *word);
tree_node_t *go_left(tree_node_t * tree);
void sizeof_bt(tree_node_t *tree, int size);

void add_word_ex(FILE *f, tree_node_t **root, char *input_word, int action, tree_node_t *find_node, hash_table_t *tabl);
void find_word_tree_ex(FILE *f, tree_node_t **root, char *input_word, hash_table_t *table);
int find_word_tree(tree_node_t **tree, char *input_word, tree_node_t **find_node);
int add_word_trr(tree_node_t **tree, char *input_word);
typedef void (*ptr_action_t)(tree_node_t *, void *);

tree_node_t *btree_insert(tree_node_t *tree, tree_node_t *node);

tree_node_t *btree_lookup_1(tree_node_t *tree, const char *name, int *count_cmp);

tree_node_t *btree_lookup_2(tree_node_t *tree, const char *name);

void btree_apply_pre(tree_node_t *tree, ptr_action_t f, void *arg);

void btree_apply_in(tree_node_t *tree, ptr_action_t f, void *arg);

void btree_apply_post(tree_node_t *tree, ptr_action_t f, void *arg);

void btree_export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree);

#endif
