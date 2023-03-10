#ifndef _OPERATIONS_H_

#define _OPERATIONS_H_

#include "errors.h"
#include "colors.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include "io.h"

#define YES             1
#define NO              0
#define NOTHING_TODEL   -1
#define NOT_CONNECTED   -2

int count_edges(graph_t *grph);
int find_notconnected(graph_t *grph);
int check_connect(graph_t *grph, int excluded);
int wannabe_tree(graph_t *grph);
size_t get_size(graph_t *grph);

#endif