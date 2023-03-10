#ifndef _MEM_ALLOC_H_

#define _MEM_ALLOC_H_

#include <stdlib.h>
#include "structures.h"

void free_array(vertex_t *array, int n);
vertex_t *calloc_array(int n);

#endif