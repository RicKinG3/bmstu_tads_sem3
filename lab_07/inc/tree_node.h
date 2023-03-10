#ifndef __TREE_NODE_H__
#define __TREE_NODE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node tree_node_t;

struct tree_node
{
    char *name;
    int count_repeat;
    int height;

    struct tree_node *left;
    struct tree_node *right;
};


 tree_node_t* node_create( char *name);


void node_print( tree_node_t *node, void *param);
void node_f(tree_node_t *node, void *param);


void node_free( tree_node_t *node, void *param);


void node_to_dot( tree_node_t *tree, void *param);


#endif	