#ifndef _GRAPHVIS_H_

#define _GRAPGVIS_H_

#include "errors.h"
#include "colors.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>

void graph_to_dot(char *cwd, char *tree_name, graph_t *, int excluded);

#endif
