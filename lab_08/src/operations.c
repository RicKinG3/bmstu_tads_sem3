#include "operations.h"

static void dfs(vertex_t *array, int *used, int from, int excluded)
{
    used[from] = YES;
    vertex_t *cur_vert = array[from].next;
    while (cur_vert)
    {
        if (cur_vert->value != excluded && used[cur_vert->value] == NO)
            dfs(array, used, cur_vert->value, excluded);
        cur_vert = cur_vert->next;
    }
}

int find_notconnected(graph_t *grph)
{
    int res = NOTHING_TODEL;
    int i = 0;
    while (i < grph->size && res == NOTHING_TODEL)
    {
        if (grph->array[i].next == NULL)
            res = i;
    }

    return res;
}

int count_edges(graph_t *grph)
{
    int result = 0;
    vertex_t *cur_vert;
    for (int i = 0; i < grph->size; i++)
    {
        cur_vert = grph->array[i].next;
        while (cur_vert)
        {
            if (cur_vert->value > i)
                result++;
            cur_vert = cur_vert->next;
        }
    }

    return result;
}

int check_connect(graph_t *grph, int excluded)
{
    int *used = calloc(grph->size, sizeof(int));
    if (excluded == 0)
        dfs(grph->array, used, 1, excluded);
    else
        dfs(grph->array, used, 0, excluded);
    
    int check = YES;
    int i = 0;
    while (i < grph->size && check == YES)
    {
        if (used[i] == NO && i != excluded)
            check = NO;
        i++;
    }
    free(used);
    if (check == NO)
        excluded = NOT_CONNECTED;

    return excluded;
}

int wannabe_tree(graph_t *grph)
{
    int to_del = NOT_CONNECTED;
    int cur_edges;
    vertex_t *cur_vert;
    int i = 0;
    while (i < grph->size && to_del == NOT_CONNECTED)
    {
        cur_edges = 0;
        cur_vert = grph->array[i].next;
       // printf(" cer vert = %d \n", cur_vert->value );
        while (cur_vert)
        {
            cur_edges++;
            cur_vert = cur_vert->next;
        }
       // printf(" cer edges = %d, edges = %d grph->size = %d \n", cur_edges, grph->edges, grph->size);

        if (grph->edges - cur_edges == grph->size - 2)//кол-во ребер - кол-во ребер у текущего узла  = кол-ву вершин -2 (тк удаляем его ) E = V - 1 
            to_del = check_connect(grph, i);
        i++;
    }
    
    return to_del;
}

size_t get_size(graph_t *grph)
{
    size_t size = 0;
    for (int i = 0; i < grph->size; i++)
    {
        vertex_t *cur_ver = grph->array + i;
        while (cur_ver)
        {
            size += sizeof(graph_t);
            cur_ver = cur_ver->next;
        }
    }

    return size;
}