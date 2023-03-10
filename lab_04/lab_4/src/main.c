#include "../inc/main_inc.h"

int main(void)
{
    int option = -1;
    int rc = -1;
    list_t *stack_list = NULL;
    arr_t stack_arr = {.arr = NULL, .len = 0};
    int max_len_list = 0, max_len_arr = 0;

    arr_clear_t clear_arr = {.len = 0};
    print_info();
    while (option != 0)
    {
        print_menu();
        rc = -1;
        rc = choose_action(&option);

        if (rc == OK)
        {
            if (option == 0)
                break;
            // запись нескольких эл в стек массив
            else if (option == 1)
            {
                if (max_len_arr != 0)
                {
                    while (max_len_arr > 0)
                    {
                        pop_arr(&stack_arr);
                        max_len_arr--;
                    }

                    max_len_arr = 0;
                }
                create_arr(&stack_arr, &max_len_arr);
            }
            // добавление одного эл в стек массив
            else if (option == 2)
            {
                if (!add_elem_arr(&stack_arr, &max_len_arr))
                    puts("\n\nЭлемент успешно добавлен\n\n");
            }
            // удаление эл из стека массив
            else if (option == 3)
            {
                if (!pop_arr(&stack_arr))
                    puts("\n\nЭлемент удален\n\n");
                else
                    puts("\nСтек пуст ( \n");
            }

            else if (option == 4)
                print_arr(stack_arr);

            else if (option == 5)
            {
                int result;

                if (!result_arr(&result))
                    printf("\n\nРезультат вычисления выражения: %d\n\n", result);
            }

            else if (option == 6)
                time_counting();
            // добавить несколько элементов в стек лист
            else if (option == 7)
            {
                if (max_len_list != 0)
                {
                    free_list(&stack_list);
                    puts("wsefewf");
                    max_len_list = 0;
                }
                rc = create_list(&stack_list, &max_len_list);

                if (rc != NO_MISTAKES)
                    printf("Код ошибки = %d", rc);

                del_adress(&clear_arr, stack_list);
            }
            //добавление одного элемента
            else if (option == 8)
            {
                if (!add_elem_list(&stack_list, &max_len_list))
                {
                    puts("\n\nЭлемент успешно добавлен\n\n");
                    del_adress(&clear_arr, stack_list);
                }
            }
            //удаление верхнего эл из стека
            else if (option == 9)
            {
                add_adress(&clear_arr, stack_list);

                if (!pop_list(&stack_list))
                    puts("\n\nЭлемент успешно удален\n\n");
            }
            //вывод стека списка
            else if (option == 10)
                print_list(stack_list);
            // вычисление
            else if (option == 11)
            {
                int result;
                if (!result_list(&result))
                    printf("\nРезультат вычисления выражения: %d\n", result);
            }
            //вывод удаленных адресов
            else if (option == 12)
                print_arr_adress(clear_arr);
            else if (option == 13)
                print_info();
        }
        else
        {
            puts("Вы ввели не верное число для выбора меню ");
            option = -1;
            continue;
        }
        option = -1;
        flush_input();
    }

    if (stack_list)
        free_list(&stack_list);

    return OK;
}