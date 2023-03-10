#include "graphvis.h"

#define BUF_SIZE 512

static void graph_print_dot_aux(graph_t *grph, FILE *stream, int excluded)
{
	for (int i = 0; i < grph->size; i++)
	{
		vertex_t *cur_ver = grph->array[i].next;
		if (i != excluded)
		{
			while (cur_ver)
			{
				if (cur_ver->value > i && cur_ver->value != excluded)
					fprintf(stream, "%d -- %d;\n", i, cur_ver->value);
				cur_ver = cur_ver->next;
			}
			fprintf(stream, "%d;\n", i);
		}
	}
}

void graph_to_dot(char *cwd, char *tree_name, graph_t *grph, int excluded)
{
	char buf[BUF_SIZE] = { 0 };
	snprintf(buf, BUF_SIZE, "%s%s.dot", cwd, tree_name);
	FILE *f = fopen(buf, "w");
	fprintf(f, "graph {\n");
	graph_print_dot_aux(grph, f, excluded);
	fprintf(f, "}\n");
	fclose(f);
}
