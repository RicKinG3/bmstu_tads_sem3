#include "../inc/tree.h"
#include "../inc/errors.h"
#include "../inc/file.h"
#include "../inc/menu_io.h"
#include "../inc/io.h"

#include <math.h>
#include <sys/time.h>
#include <time.h>

extern char *strdup(const char *);
#include <string.h>
#include <stdlib.h>

#define HIGNT 2

void make_binary_tree(tree_node_t **tree, tree_node_t *arr, size_t len)
{
    if (len == 0)
        return;

    tree_node_t *node = node_create(arr[len / 2].name);
    *tree = btree_insert(*tree, node);
    make_binary_tree(tree, arr, len / 2);
    make_binary_tree(tree, arr + len / 2, len / 2);
}
void file_arr_in_f(FILE *f, tree_node_t *arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (i + 1 == len)
            fprintf(f, "%s", arr[i].name);
        else
        {
            fprintf(f, "%s\n", arr[i].name);
        }
    }
}

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

void btree_post(tree_node_t *tree, char **name)
{
    if (tree == NULL)
        return;

    btree_post(tree->left, name);
    *name = tree->name;
    btree_post(tree->right, name);
}

#define MEASURE_SIZE 1000
#define MEASURMENT_STEP 100
#define STEP 5

#define TRIES 10000
#include <stdbool.h>

void print_measurement(void)
{
    tree_node_t *tree = NULL;
    tree_node_t arr[MEASURE_SIZE];
    size_t len = 0;

    long long unsigned beg, end;
    unsigned long long delt = 0, delt_f = 0;

    char str[100];
    char temp[10] = {0};
    int max_size_num = 5;

    for (int i = 1; i < MEASURE_SIZE; i++)
    {

        int tenp_i = i;
        int size = 0;
        while (tenp_i > 0)
        {
            ++size;
            tenp_i /= 10;
        }

        int count_nul = max_size_num - size;
        for (int j = 0; j < count_nul; j++)
            temp[j] = '0';
        temp[count_nul] = '\0';

        sprintf(str, "%s%d", temp, i);

        char *s = strdup(str);
        arr[i - 1].name = s;
        arr[i - 1].count_repeat = 1;
        len++;
    }

    puts("Tree nodes amount - общее количество узлов в дереве, tree depth - высота дерева");
    printf("|%-30s|%-30s|%-30s|%-30s|\n", "Tree nodes amount", "Tree depth", "Search in balanced (ms)", "Search in file (ms)");
    puts("------------------------------------------------------------------------------------------------------------------------");
    tree_node_t *finf_w = NULL;
    for (size_t i = STEP; i < MEASURE_SIZE; i += STEP)
    {

        btree_apply_pre(tree, node_f, NULL);

        remove("data/meansuare.txt");
        FILE *f = fopen("data/meansuare.txt", "w+");
        tree = NULL;
        delt = 0;
        delt_f = 0;

        make_binary_tree(&tree, arr, i);

        tree_node_t last = arr[i - 2];
        // printf_tree_and_gener_gv(tree);
        // puts(last.name);
        if (find_word_tree(&tree, last.name, &finf_w) == IS_FIND_WORD)
        {
            for (size_t j = 0; j < TRIES; j++)
            {
                beg = milliseconds_now();
                btree_lookup_1(tree, last.name);

                end = milliseconds_now();
                delt += end - beg;
            }
            printf("|%-30zu|", i);
            printf("%-30d|", (int)ceil(log2(i)));
            printf("%-30lf|", (double)delt / TRIES);
            rewind(f);
            file_arr_in_f(f, arr, i);
            rewind(f);
            // print_file(f);
            rewind(f);

            for (size_t j = 0; j < TRIES; j++)
            {
                beg = milliseconds_now();
                rewind(f);
                find_word_file(f, last.name);
                end = milliseconds_now();
                delt_f += end - beg;
            }
            {

                printf("%-30lf|\n", (double)delt_f / TRIES);
            }
        }
    }

    generate_gv_ex(tree, "data/balace_tree.gv");
    btree_apply_pre(tree, node_f, NULL);
    tree = NULL;

    puts("------------------------------------------------------------------------------------------------------------------------");

    puts("Left-side и Right-side - деревья у которых узлы расположены по левую или правую сторону соответственно");
    printf("|%-20s|%-28s|%-20s|%-28s|%-28s|\n", "Tree nodes amount", "Search in left-side tree (ms)", "Search in file", "Search in right-side tree (ms)", "Search in file");
    puts("------------------------------------------------------------------------------------------------------------------------");
    size_t new_tries = TRIES;
    for (size_t i = MEASURMENT_STEP / 10; i < MEASURE_SIZE / 10 + 1; i += MEASURMENT_STEP / 10)
    {

        tree_node_t last_w = arr[0];
        tree_node_t last_w_2 = arr[i - 2];
        btree_apply_pre(tree, node_f, NULL);
        tree = NULL;
        FILE *f = fopen("data/1meansuare.txt", "w+");

        // tree_node_t *node_t_1 = node_create(arr[i - 1].name);
        // tree = btree_insert(tree, node_t_1);
        // tree_node_t *node_t = node_create("99999999999999");
        // tree = btree_insert(tree, node_t);
        for (int j = i - 1; j >= 0; j--)
        {
            tree_node_t *node = node_create(arr[j].name);
            tree = btree_insert(tree, node);
        }

        delt = 0;
        delt_f = 0;
        if (find_word_tree(&tree, last_w.name, &finf_w) == IS_FIND_WORD && find_word_tree(&tree, last_w_2.name, &finf_w) == IS_FIND_WORD)
        {
            printf("|%-20zu|", i);
            for (size_t j = 0; j < new_tries; j++)
            {
                beg = milliseconds_now();
                btree_lookup_1(tree, last_w.name);
                end = milliseconds_now();
                delt += end - beg;
            }

            printf("%-28lf|", (double)delt / new_tries);
            if (i == MEASURE_SIZE / 10)
                generate_gv_ex(tree, "data/left_tree.gv");

            rewind(f);
            file_arr_in_f(f, arr, i);
            for (size_t j = 0; j < new_tries; j++)
            {
                beg = milliseconds_now();
                rewind(f);
                find_word_file(f, last_w.name);

                end = milliseconds_now();
                delt_f += end - beg;
            }
            {
                printf("%-20lf|", (double)delt_f / new_tries);
            }

            btree_apply_pre(tree, node_f, NULL);
            tree = NULL;
            fclose(f);
            f = fopen("data/1meansuare.txt", "w+");

            for (int j = 0; j < (int)i; j++)
            {
                tree_node_t *node = node_create(arr[j].name);
                tree = btree_insert(tree, node);
            }

            delt = 0;
            delt_f = 0;

            for (size_t j = 0; j < new_tries; j++)
            {
                beg = milliseconds_now();
                btree_lookup_1(tree, last_w_2.name);
                end = milliseconds_now();

                delt += end - beg;
            }
            printf("%-28lf|", (double)delt / new_tries);
            rewind(f);
            file_arr_in_f(f, arr, i);
            rewind(f);

            for (size_t j = 0; j < new_tries; j++)
            {
                beg = milliseconds_now();
                rewind(f);
                find_word_file(f, last_w_2.name);

                end = milliseconds_now();
                delt_f += end - beg;
            }
            {
                printf("%-28lf| \n", (double)delt_f / new_tries);
            }
            generate_gv_ex(tree, "data/right_tree.gv");
            btree_apply_pre(tree, node_f, NULL);
            tree = NULL;
        }
    }

    // printf_tree_and_gener_gv(tree);
    puts("------------------------------------------------------------------------------------------------");

    printf("Замер для сбалансированного дерева проведен %d раз\n", TRIES);
    printf("Замеры для левостороннего и правостороннего деревьев проведены %zu раз\n", new_tries);
}
