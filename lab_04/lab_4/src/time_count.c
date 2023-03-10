#include "../inc/time_count.h"

#define MAX_N 1000

void print_time(int64_t start1, int64_t end1, int64_t start2, int64_t end2)
{
    printf("\nМАССИВ: %.10lf секунд\n", (double)(end1 - start1) / GHZ);
    printf("СПИСОК: %.10lf секунд\n", (double)(end2 - start2) / GHZ);
}

void create_rand_nums(int *arr, int count)
{
    srand(time(NULL));

    for (int i = 0; i < count; i++)
    {
        int num = rand() % 10;
        arr[i] = num;
    }
}

void time_add(int count)
{
    int64_t start1 = 0, end1 = 0, start2 = 0, end2 = 0;

    list_t *stack_list = create_node(33);
    arr_t stack_arr = {.arr = NULL, .len = 0};

    int *tmp = malloc(count * sizeof(int));

    if (!tmp)
        return;

    stack_arr.arr = tmp;

    int arr[MAX_N];

    create_rand_nums(arr, count);

    for (int j = 0; j < RUNS; j++)
    {
        start1 += tick();
        for (int i = 0; i < count; i++)
        {
            push_arr(&stack_arr, arr[i]);
        }
        end1 += tick();

        start2 += tick();
        for (int i = 0; i < count; i++)
        {
            push_node(&stack_list, arr[i]);
        }
        end2 += tick();

        for (int i = 0; i < count; i++)
        {
            pop_arr(&stack_arr);
            pop_list(&stack_list);
        }
    }

    puts("\nЗамеры добавления элемента");
    print_time(start1 / RUNS, end1 / RUNS, start2 / RUNS, end2 / RUNS);

    free_list(&stack_list);
    free(tmp);
}

void time_del(int count)
{
    int64_t start1 = 0, end1 = 0, start2 = 0, end2 = 0;

    list_t *stack_list = create_node(33);
    arr_t stack_arr = {.arr = NULL, .len = 0};

    int *tmp = malloc(count * sizeof(int));

    if (!tmp)
        return;

    stack_arr.arr = tmp;

    int arr[MAX_N];

    create_rand_nums(arr, count);

    for (int j = 0; j < RUNS; j++)
    {
        for (int i = 0; i < count; i++)
        {
            push_arr(&stack_arr, arr[i]);
            push_node(&stack_list, arr[i]);
        }

        start1 += tick();
        for (int i = 0; i < count; i++)
        {
            pop_arr(&stack_arr);
        }
        end1 += tick();

        start2 += tick();
        for (int i = 0; i < count; i++)
        {
            pop_list(&stack_list);
        }
        end2 += tick();
    }

    puts("\nЗамеры удаления элемента");
    print_time(start1 / RUNS, end1 / RUNS, start2 / RUNS, end2 / RUNS);

    free_list(&stack_list);
    free(tmp);
}

void time_process(int count)
{
    int64_t start1 = 0, end1 = 0, start2 = 0, end2 = 0;

    int arr[MAX_N];

    create_rand_nums(arr, count);

    expres_t expression;
    int flag = 0;

    for (int i = 0; i < count; i++)
    {
        if (!flag)
        {
            expression.sym[i] = arr[i] + '0';
            flag = 1;
        }
        else
        {
            expression.sym[i] = '+';
            flag = 0;
        }
    }

    expression.sym[count - 1] = '1';
    expression.sym[count] = '\0';

    expression.len = count;

    for (int i = 0; i < RUNS; i++)
    {
        start1 += tick();
        calculate_arr(expression);
        end1 += tick();

        start2 += tick();
        calculate_list(expression);
        end2 += tick();
    }

    puts("\nЗамеры вычисления выражения");
    print_time(start1 / RUNS, end1 / RUNS, start2 / RUNS, end2 / RUNS);
}

void time_counting(void)
{
    puts("\nВведите количество элементов в стеках ∈ [1, 1000] :");
    int count;

    int rc = input_int(&count);

    if ((rc != PASS) || (count < 1) || (count > 1000))
    {
        puts("\nОшибка: неверно введено количество элементов в стеках\n");
        return;
    }

    printf("\nВ стеках по %d элементов", count);

    time_add(count);
    time_del(count);
    time_process(count);

    printf("\nКол-во памяти для %d элементов: \
        \nМассив: %ld байт\
        \nСписок: %ld байт\n\n",
           count, count * sizeof(int) + sizeof(int *), count * sizeof(list_t));
}