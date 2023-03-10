#include "../inc/tree.h"
#include "../inc/errors.h"
#include "../inc/file.h"
#include "../inc/menu_io.h"
#include "../inc/io.h"

#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

void srand48(long seedval);
extern char *strdup(const char *);
double drand48(void);
#include <string.h>
#include <stdlib.h>

#define HIGNT 2

void shuffle(tree_node_t *array, size_t n)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int usec = tv.tv_usec;
    srand48(usec);

    if (n > 1)
    {
        size_t i;
        for (i = n - 1; i > 0; i--)
        {
            size_t j = (unsigned int)(drand48() * (i + 1));
            tree_node_t t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void make_binary_tree(tree_node_t **tree, tree_node_t *arr, size_t len)
{
    if (len == 0)
        return;

    tree_node_t *node = node_create(arr[len / 2].name);
    *tree = btree_insert(*tree, node);
    make_binary_tree(tree, arr, len / 2);
    make_binary_tree(tree, arr + len / 2, len / 2);
}

void make_binary(tree_node_t **tree, tree_node_t *arr, size_t len)
{
    if (len == 0 || len - 1 == 0)
        return;

    int t = 80 + rand() % 100;
    if (t % 2 == 0)
    {
        tree_node_t *node = node_create(arr[len / 2].name);

        *tree = btree_insert(*tree, node);
        make_binary(tree, arr, len / 2);
        make_binary(tree, arr + len / 2, len / 2);
    }
    else
    {
        tree_node_t *node = node_create(arr[len - 2].name);
        *tree = btree_insert(*tree, node);
        make_binary(tree, arr + len / 2, len / 2);
        make_binary(tree, arr, len / 2);
    }
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

#define MEASURE_SIZE 100000
#define MEASURMENT_STEP 100
#define STEP 1000

#define TRIES 100000

#include <stdbool.h>

void print_measurement(void)
{
    tree_node_t *tree = NULL, *tree_ddp = NULL;
    tree_node_t arr[MEASURE_SIZE];
    tree_node_t arr_ddp[MEASURE_SIZE];

    size_t len = 0;

    long long unsigned beg, end;
    unsigned long long delt = 0, delt_f = 0, delt_ddp = 0;

    char str[100];
    char temp[10] = {0};
    int max_size_num = 5;
    int count_cmp = 0;

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
        char *s1 = strdup(str);

        arr[i - 1].name = s;
        arr[i - 1].count_repeat = 1;
        arr_ddp[i - 1].name = s1;
        arr_ddp[i - 1].count_repeat = 1;

        len++;
    }

    // shuffle(arr_ddp, len);
    puts("Tree nodes amount (TNA) - общее количество узлов в дереве, tree depth (TD) - высота дерева, ");
    puts("Поиск в сбалансированном дереве (ms) = balanced, Поиск в не сбалансированном дереве (ms) = DDP, Search in hash table (ms) = hash");
    puts("");
    printf("|%-7s|%-7s|%-35s|%-35s|%-35s|\n", "TNA", "TD", "balanced", "DDP", "HASH");
    puts("------------------------------------------------------------------------------------------------------------------------");
    tree_node_t *finf_w = NULL;
    hash_table_t table;

    for (size_t i = STEP; i < MEASURE_SIZE; i += STEP)
    {

        btree_apply_pre(tree, node_f, NULL);
        btree_apply_pre(tree_ddp, node_f, NULL);

        remove("data/meansuare.txt");
        FILE *f = fopen("data/meansuare.txt", "w+");
        tree = NULL;
        tree_ddp = NULL;

        delt = 0;
        delt_ddp = 0;
        delt_f = 0;
        count_cmp = 0;
        make_binary_tree(&tree, arr, i);
        make_binary(&tree_ddp, arr_ddp, i);

        int t = rand() % i;

        tree_node_t last  = arr[t];
        tree_node_t *ggg = go_left(tree);

        // printf_tree_and_gener_gv(tree);

        if (find_word_tree(&tree_ddp, last.name, &finf_w) == IS_FIND_WORD && find_word_tree(&tree, last.name, &finf_w) == IS_FIND_WORD)
        {
            

            for (size_t j = 0; j < TRIES; j++)
            {
                t = rand() % i;
                beg = milliseconds_now();
                btree_lookup_1(tree, last.name, &count_cmp);
                end = milliseconds_now();
                last = arr[t];
                delt += end - beg;
            }
            printf("|%-7zu|", i);
            printf("%-7d|", (int)ceil(log2(i)));

            printf("%-15lf {%-4d} {%-10ld}|", (double)delt / TRIES, count_cmp / TRIES, i * sizeof(tree_node_t));
            count_cmp = 0;
            // ddp
            for (size_t j = 0; j < TRIES; j++)
            {
                t = rand() % i;
                beg = milliseconds_now();
                btree_lookup_1(tree_ddp, last.name, &count_cmp);
                end = milliseconds_now();
                last = arr[t];
                delt_ddp += end - beg;
            }
            printf("%-15lf {%-4d} {%-10ld}|", (double)delt_ddp / TRIES, count_cmp / TRIES, i * sizeof(tree_node_t));

            rewind(f);
            file_arr_in_f(f, arr, i);
            free_table(&table);
            hash_table_init(&table, i);

            rewind(f);
            create_hash_table(f, &table);
            rewind(f);

            int count_cmprs = count_cmp;
            int is_find = PASS;
            count_cmp = 0;

            for (size_t j = 0; j < TRIES; j++)
            {
                beg = milliseconds_now();
                hash_find_in_table(&table, ggg->name, count_cmprs, &is_find, &count_cmp);
                if (is_find == NOT_FOUND)
                    puts("edfe");
                end = milliseconds_now();
                delt_f += end - beg;
                last = arr[t];
            
            }
            printf("%-15lf {%-4d} {%-10ld}|\n", (double)delt_f / TRIES, count_cmp / TRIES, (20 +8) * i);
        }
    }

    generate_gv_ex(tree, "data/balace_tree.gv");
    generate_gv_ex(tree_ddp, "data/not_balace_tree.gv");

    btree_apply_pre(tree, node_f, NULL);
    btree_apply_pre(tree_ddp, node_f, NULL);

    tree = NULL;
    tree_ddp = NULL;

    puts("------------------------------------------------------------------------------------------------------------------------");

    // printf_tree_and_gener_gv(tree);
    //puts("------------------------------------------------------------------------------------------------");

    printf("Замер для первой таблицы  проведен %d раз\n", TRIES);
}

#define COUNT_ADD_EL 10000
#define  START_ADD 1000
#define STEP_ADD 50
void print_measurement_add(void)
{
    tree_node_t *tree = NULL;
    hash_table_t table;

    tree_node_t arr[1];

    long long unsigned beg, end;
    unsigned long long delt_hash = 0, delt_ddp = 0;

    arr[0].count_repeat = 1;
    arr[0].name = "qew";
    arr[0].height = 1;

    char str[100];
    char temp[10] = {0};
    int max_size_num = 5;
    // int count_cmp = 0;

    FILE *f = fopen("data/2.txt", "w+");
    rewind(f);
    file_arr_in_f(f, arr, 1);
    hash_table_init(&table, (COUNT_ADD_EL ));
    create_hash_table(f, &table);

    printf("|%-7s|%-35s|%-35s|\n", "count_w", "DDP", "HASH");
    puts("------------------------------------------------------------------------------------------------------------------------");
    for (int i = START_ADD; i < COUNT_ADD_EL; i+= STEP_ADD)
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
        char *s1 = strdup(str);

        delt_hash = 0;
        delt_ddp = 0;

        for (size_t j = 0; j < TRIES; j++)
        {
            beg = milliseconds_now();
            add_word_trr(&tree, s1);
            end = milliseconds_now();
            delt_hash += end - beg;
        }
        
        printf("|%-7u|", i);
        printf("%-35lf |", (double)delt_ddp / TRIES);
        
        for (size_t j = 0; j < TRIES; j++)
        {
            beg = milliseconds_now();
            add_word_to_hash_table(&table, s);
            
            end = milliseconds_now();
            delt_hash += end - beg;
        }


        printf("%-35lf |\n", (double)delt_hash / TRIES);
    }
        print_table(&table);
        printf_tree_and_gener_gv(tree);

}