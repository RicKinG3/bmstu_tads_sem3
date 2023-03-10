#include "mem_alloc.h"

vertex_t *calloc_array(int n)
{
    vertex_t *array = malloc(sizeof(vertex_t) * n);
    for (int i = 0; i < n; i++)
    {
        array[i].value = i;
        array[i].next = NULL;
    }

    return array;
}

void free_array(vertex_t *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        vertex_t *cur_vert = array[i].next;
        while (cur_vert)
        {
            vertex_t *tmp = cur_vert;
            cur_vert = cur_vert->next;
            free(tmp);
        }
    }
    free(array);
}
