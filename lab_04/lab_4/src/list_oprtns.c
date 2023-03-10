#include "../inc/list_oprtns.h"

list_t *create_node(const int num)
{
    list_t *tmp_elem = malloc(sizeof(list_t));

    if (!tmp_elem)
        return NULL;

    tmp_elem->num = num;
    tmp_elem->ind = 0;
    tmp_elem->next = NULL;

    return tmp_elem;
}

int push_node(list_t **list, const int num)
{
    list_t *node = create_node(num);

    if (!node)
    {
        return ERR_ALLOCATE_MEMORY;
    }

    node->ind = (*list)->ind + 1;
    node->next = *list;

    *list = node;

    return OK_PUSH;
}

int pop_list(list_t **list)
{
    if (!(*list))
    {
        puts("\nСтек пуст(\n");
        return STACK_IS_CLEAR;
    }
    list_t *tmp = (*list)->next;
    free(*list);
    *list = tmp;

    return OK_DEL;
}

void free_list(list_t **list)
{
    int len = (*list)->ind;

    while (len >= 0)
    {
        pop_list(list);
        len--;
    }
}

int add_elem_list(list_t **list, int *max_len)
{
    int rc = PASS;

    if (*max_len == 0)
       rc = input_max_len_stack(max_len);
    if (rc != PASS)
        return rc;

    if (*list)
    {
        if ((*list)->ind + 2 > *max_len)
        {
            puts("\nОшибка: стек переполнен\n");
            return ERR_OWERFLOW_STACK;
        }
    }
    int num;

    puts("\nВведите число:");
    rc = input_int(&num);

    if ((rc != PASS))
    {
        puts("\nОшибка: неверно введен элемент для добавления\n");
        return ERR_UNRIGHT_ELEM;
    }

    // Add to list

    if (!(*list))
        *list = create_node(num);
    else
    {
        rc = push_node(list, num);

        if (rc != NO_MISTAKES)
            return rc;
    }

    return OK_ADD;
}

int print_list(list_t *list)
{
    if (!list)
    {
        puts("\n\nСтек пуст\n\n");
        return STACK_IS_CLEAR;
    }

    int len = list->ind;
    puts("\nСтек в виде списка\n");

    list_t *tmp = list;

    while (len >= 0)
    {
        printf("%3d -- %p\n", tmp->num, (void *)tmp);
        tmp = tmp->next;

        len--;
    }
    return OK_PRINT;
}



int create_list(list_t **stack_list, int *max_len)
{
    int rc = PASS;
    if (*max_len == 0)
        rc = input_max_len_stack(max_len);
    if (rc != PASS)
        return rc;

    printf("\nВведите кол-во эл. ∈ [1, %d]:\n", *max_len);
    int cur_len = 0;
    rc = input_int(&cur_len);

    if (rc != PASS || (cur_len < 1) || (cur_len > *max_len))
    {
        puts("\nОшибка: Вы ввели неверно количество элементов в стеке\n");
        return ERR_UNRIGHNT_CUR_SIZE_LIST;
    }

    int num;
    puts("\nВведите элементы по одному:");

    for (int i = 0; i < cur_len; i++)
    {
        rc = input_int(&num);

        if (rc != PASS)
        {
            puts("\nОшибка: Вы ввели неверно, *числа целые,  повторите попытку\n");
            i--;
        }

        else
        {
            if (!(*stack_list))
                *stack_list = create_node(num);
            else
            {
                int rc = push_node(stack_list, num);

                if (rc != NO_MISTAKES)
                    return rc;
            }
        }
    }

    puts("\nЗначения в стек в виде списка успешно добавлены\n");

    return OK_CREATE;
}

int check_clear_stack_list(list_t *list)
{
    return (!list) ? CLEAR : INITED;
}

int top_list(list_t *list)
{
    return (list->num);
}

void count_operation_list(list_t **num_stack, list_t **sign_stack)
{
    int num1 = top_list(*num_stack);
    pop_list(num_stack);

    int num2 = top_list(*num_stack);
    pop_list(num_stack);

    int sign_op = top_list(*sign_stack);
    pop_list(sign_stack);

    int result;

    if (sign_op == 1)
    {
        result = num2 + num1;
    }
    else if (sign_op == 2)
    {
        result = num2 - num1;
    }
    else if (sign_op == 3)
    {
        result = num2 * num1;
    }
    else if (sign_op == 4)
    {
        result = (int)(num2 / num1);
    }

    // printf("\n\nCOUNT: %d (%d) %d = %d\n\n", num1, sign_op, num2, result);

    if (!check_clear_stack_list(*num_stack))
    {
        *num_stack = create_node(result);
    }
    else
    {
        push_node(num_stack, result);
    }

    // print_arr(*num_stack);
}

int calculate_list(expres_t exp)
{
    list_t *num_stack = NULL;
    list_t *sym_stack = NULL;

    for (int i = 0; i < exp.len; i++)
    {

        if (check_operation(exp.sym[i])) // if sign
        {
            int sign = translate_operation(exp.sym[i]);

            if (!check_clear_stack_list(sym_stack)) // if stack clear
            {
                sym_stack = create_node(sign);
            }
            else // if stack is not clear
            {
                int level_cur = check_priority(sign);
                int level_prev = check_priority(top_list(sym_stack));

                if (level_cur > level_prev) // if priority is higher
                    push_node(&sym_stack, sign); // push in stack
    
                else if (level_cur <= level_prev) // if priority is equal or lower
                {
                    count_operation_list(&num_stack, &sym_stack); // take 2 nums from stack and prev sign -> result in num_stack
                    i--;
                }
            }
        } // end sign parse
        else
        {
            int num = read_num_from_arr_char(exp.sym, &i); // get num from stack
            i -= 1;


            if (!check_clear_stack_list(num_stack))
                num_stack = create_node(num);
            else
                push_node(&num_stack, num);

            if (i + 1 == exp.len)
                while (check_clear_stack_list(sym_stack)) // if operations are left after loop
                {
                    count_operation_list(&num_stack, &sym_stack);
                }
        } // end num parse

        
    }

    return top_list(num_stack);
}

int result_list(int *res)
{
    expres_t exp;

    int rc = read_expression(&exp);

    if (rc != NO_MISTAKES)
        return rc;

    *res = calculate_list(exp);

    return OK_COUNT;
}

void add_adress(arr_clear_t *arr, list_t *list)
{
    if (!list)
        return;

    int ind = arr->len;
    arr->arr_clear[ind] = list;
    arr->len += 1;
}

void adress_clear(arr_clear_t *arr, int ind)
{
    for (int i = ind; i < arr->len - 1; i++)
    {
        list_t *tmp = arr->arr_clear[i];
        arr->arr_clear[i] = arr->arr_clear[i + 1];
        arr->arr_clear[i + 1] = tmp;
    }
}

void del_adress(arr_clear_t *arr, list_t *list)
{
    if (!list)
    {
        return;
    }
    list_t *tmp = list;
    int len = tmp->ind;

    for (int i = 0; i < arr->len; i++)
    {
        tmp = list;
        for (int j = len; j >= 0; j--)
        {
            if (arr->arr_clear[i] == tmp)
            {
                adress_clear(arr, i);
                arr->len -= 1;
                LOG_DEBUG("elem %d cleared", i);
                i--;
            }

            tmp = tmp->next;
        }
    }
}

void print_arr_adress(arr_clear_t arr)
{
    if (arr.len == 0)
    {
        puts("\n\nМассив освободившихся адрессов пуст\n\n");
        return;
    }

    int len = arr.len;

    puts("\n\nМассив освободившихся адрессов\n");

    for (int i = 0; i < len; i++)
    {
        printf("%p ", (void *)arr.arr_clear[i]);
    }

    puts("\n");
}
