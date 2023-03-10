#include "io.h"

void insert(vertex_t *array, int from, int to)
{
    vertex_t *cur_vert = array + from;
    while (cur_vert->next)
        cur_vert = cur_vert->next;
    cur_vert->next = malloc(sizeof(vertex_t));
    cur_vert->next->value = to;

    cur_vert = array + to;
    while (cur_vert->next)
        cur_vert = cur_vert->next;
    cur_vert->next = malloc(sizeof(vertex_t));
    cur_vert->next->value = from;
}

int read_graph(FILE *f, graph_t *grph)
{
    if (!f)
        return INVALID_INPUT;

    int n; 
    int rc = fscanf(f, "%d", &n);
    
    if (!rc || n < 1)
        return INVALID_INPUT;

    grph->size = n;
    grph->array = calloc_array(n);
    int cur_from, cur_to;
    
    if (!grph->array)
        return ALLOC_ERROR;
    
    while ((rc = fscanf(f, "%d%d", &cur_from, &cur_to)) == 2)
    {
        if (cur_from == cur_to)
        {
            free_array(grph->array, n);
            printf("Граф не может быть зациклен на себя. Выход из программы\n");

            return INVALID_INPUT;
        }
        if (cur_from < 0 || cur_from > n - 1 || cur_to < 0 || cur_to > n - 1)
        {
            free_array(grph->array, n);
            printf("Встречено неверное значение. Выход из программы\n");

            return INVALID_INPUT;
        }
        insert(grph->array, cur_from, cur_to);
    }
    
    if (rc == 1)
    {
        free_array(grph->array, n);
        printf("Встречено неверное значение. Выход из программы.\n");

        return INVALID_INPUT;
    }
    rewind(f);

    return 0;    
}
