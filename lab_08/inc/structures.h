#ifndef _STRUCTURES_H_

#define _STRUCTURES_H_

#include <stdlib.h>

typedef struct vertex
{
    int value;
    struct vertex *next;
} vertex_t;

typedef struct graph
{
    int size;
    int edges;
    vertex_t *array;
} graph_t;

#endif