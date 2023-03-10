#include "io.h"
#include "errors.h"
#include "colors.h"
#include <time.h>
#include "structures.h"
#include "operations.h"
#include "graphvis.h"
#include "timer.h"

/*
Задан граф - не дерево. Проверить, можно ли
превратить его в дерево удалением одной
вершины вместе с ее ребрами.
*/

int main(int args, char **keys)
{
    uint64_t t;
    int tmp, tmp_rc;
    int error_code = NO_ERROR;
    FILE *f;
    graph_t grph;
    if (args != 2 || (f = fopen(keys[1], "r")) == NULL || (tmp_rc = fscanf(f, "%d", &tmp)) == EOF || tmp_rc == 0)
    {
        printf("Ошибка: открытие файла не возможно\n");
        return INVALID_INPUT;
    }
    rewind(f);
    char graphs_dir[] = "graphs/";
    char graph_name[] = "graph";
    char graph_del_name[] = "new_graph";
    char command[BUFSIZ];
    // создается массив где в i позиции хранится список достяжимости этой i вершины 
    error_code = read_graph(f, &grph);
    fclose(f);
    graph_to_dot(graphs_dir, graph_name, &grph, NOTHING_TODEL);
    snprintf(command, BUFSIZ, "dot -Tpng %s%s.dot -o %s%s.png", graphs_dir, graph_name, graphs_dir, graph_name);
    system(command);

    printf("Построение исходного графа, графическое построение сохранено в graphs/graph.png\n");
   
   
    if (error_code == NO_ERROR)
    {
        grph.edges = count_edges(&grph);
        int todel;
        t = tick();
        if (grph.edges == grph.size - 1)
        {
            todel = check_connect(&grph, NOTHING_TODEL);
            if (todel == NOT_CONNECTED)
            {
                int n = find_notconnected(&grph);
                if (n != NOTHING_TODEL)
                    todel = check_connect(&grph, n);
            }
        }
        else
            todel = wannabe_tree(&grph);
        t = tick() - t;

        if (todel == NOTHING_TODEL)
            printf("Граф уже является деревом\n" );
        else if (todel == NOT_CONNECTED)
            printf("Перестройка из графа в дерево невозможно\n" );
        else
        {
            printf("\nДля преобразования графа в дерево,\nнеобходимо удалить {%d} узел\n\n", todel);
            graph_to_dot(graphs_dir, graph_del_name, &grph, todel);
            snprintf(command, BUFSIZ, "dot -Tpng %s%s.dot -o %s%s.png", graphs_dir, graph_del_name, graphs_dir, graph_del_name);
            
            system(command);
            printf("Посторение нового графа дерева, графическое построение сохранено в graphs/new_graph.png\n");

        
        }
        printf( "\nНа нахождение нужного узла было затрачено %ld тиков\n" , t);
        printf( "Граф, на основе списка смежности занимает %ld байт\n" , get_size(&grph));
        free_array(grph.array, grph.size);
    }
    else if (error_code == INVALID_INPUT)
        printf("Ошибка: некорректные данные в файле\n");
        

    return error_code;
}
