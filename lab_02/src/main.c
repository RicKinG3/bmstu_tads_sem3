#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../inc/struct_inf_stdnt.h"
#include "../inc/error.h"
#include "../inc/check_str.h"
#include "../inc/rw_student.h"
#include "../inc/sort_std.h"

#define MODE_NOSORT 0
#define MODE_SORT 1
#define START_NULL 0

int main(void)
{
    inf_stdnt_t arr_stdnt[MAX_STDNT];
    key_tables_t arr_key[MAX_LEN_STR];
    int rc = PASS;

    char count_stdnt[MAX_LEN_STR] = {0};
    int num_count_std;
    char temp[MAX_LEN_STR] = {0};

    FILE *f = fopen("in.txt", "r");
    if (f == NULL)
        return ERR_OPEN;

    int menu = 1;
    print_info();
    // первый запуск позволяет выбрать от куда подгружать из файла или вводить
    printf("Если хотите самостоятельно заполнить структуру введите число отличное от 0 целое, если из файла, то введите 0: ");

    if (read_line(temp, sizeof(temp), stdin) != PASS)
    {
        puts("Вы ввели не целое число для выбора, по этому чтение из файла");
        menu = 0;
    }
    if (check_int(temp))
    {
        puts("Вы ввели не целое число для выбораб по этому чтение из файла");
        menu = 0;
    }
    menu = atoi(temp);
    memset(temp, '\0', sizeof(temp));
    rc = item_input(f, arr_stdnt, count_stdnt, &num_count_std, menu);
    print_error_input(rc);
    menu = 1;

    while (menu)
    {
        print_menu();
        printf("\nДля выбора меню введите целое число : ");
        if (read_line(temp, sizeof(temp), stdin) != PASS)
        {
            puts("Вы ввели не целое число для выбора");
            menu = 20;
            memset(temp, '\0', sizeof(temp));
        }
        if (check_int(temp))
        {
            puts("Вы ввели не целое число для выбора");
            menu = 20;
            memset(temp, '\0', sizeof(temp));
        }
        if (menu == 20)
        {
            menu = 1;
            printf("\nВы ввели не верный выбор меню\n");
            continue;
        }
        else
        {
            menu = atoi(temp);
            memset(temp, '\0', sizeof(temp));
        }

        if (menu == 0)
            break;

        /*добавления записей в конец таблицы */
        if (menu == 1)
        {
            num_count_std++;
            if (num_count_std > MAX_STDNT)
            {
                puts("Невозможно добавить студента, кол-во студентов больше 40");
                continue;
            }

            rc = input_stdnt(arr_stdnt, num_count_std, stdin, LOUD_INPUT, num_count_std - 1);
            print_error_input(rc);
            if (rc != PASS)
            {
                rc = PASS;
                del_stdnt(arr_stdnt, &num_count_std, 0);
            }
        }
        else if (menu == 2)
        {
            if (num_count_std > 1)
            {

                printf("\nВведите целое число для удаления по году поступления: ");
                char tmp_yaer[MAX_LEN_STR] = {0};
                int temp_int = 0;
                if (read_line(tmp_yaer, sizeof(tmp_yaer), stdin) == ERR_READ)
                {
                    rc = ERR_YEAR;
                    printf("\nОшибка ввода года поступления для удаления");
                }
                else if (check_int(tmp_yaer))
                {
                    rc = ERR_YEAR;
                    printf("\nОшибка ввода года поступления для удаления не верный формат");
                }
                temp_int = atoi(tmp_yaer);
                if (temp_int <= 1900 || temp_int > 2023)
                {
                    printf("\nОшибка ввода года поступления для удаления не верный диапозон");
                    rc = ERR_YEAR;
                }
                if (rc == PASS)
                {
                    rc = del_stdnt(arr_stdnt, &num_count_std, temp_int);
                    if (rc)
                    {
                        printf("\nВы удалили всех студентов");
                    }
                }
                rc = PASS;
            }
            else
                printf("\nВы не можете удалить студента, так как количество студентов = 1");
        }

        else if (menu == 3)
        {
            printf("\nВведите целое число для вывода списока студентов, указанного года поступления, живущих в общежитии: ");
            char tmp_yaer[MAX_LEN_STR] = {0};
            int temp_int = 0;
            if (read_line(tmp_yaer, sizeof(tmp_yaer), stdin) == ERR_READ)
            {
                rc = ERR_YEAR;
                printf("\nОшибка ввода года поступления для удаления");
            }
            else if (check_int(tmp_yaer))
            {
                rc = ERR_YEAR;
                printf("\nОшибка ввода года поступления для удаления не верный формат");
            }
            temp_int = atoi(tmp_yaer);
            if (temp_int <= 1900 || temp_int > 2023)
            {
                printf("\nОшибка ввода года поступления для удаления не верный диапозон");
                rc = ERR_YEAR;
            }
            if (!rc)
                print_stnt_hostel_by_year(arr_stdnt, num_count_std, temp_int);
            else
                puts("ERR");
        }
        //просмотр отсортированной таблицы ключей
        else if (menu == 4)
        {
            input_key_tables(arr_stdnt, arr_key, num_count_std);
            sort_key_mergesort(arr_key, START_NULL, num_count_std - 1);
            print_key_tables(arr_key, num_count_std);
        }
        //Выыести отсортированную структуру
        else if (menu == 5)
        {
            sort_std(arr_stdnt, START_NULL, num_count_std - 1);
            print_stdnt(arr_stdnt, arr_key, num_count_std, MODE_NOSORT);
        }
        //вывод исходной таблицы в упорядоченном виде, используя упорядоченную таблицу ключе
        else if (menu == 6)
        {
            input_key_tables(arr_stdnt, arr_key, num_count_std);
            sort_key_mergesort(arr_key, START_NULL, num_count_std - 1);
            print_stdnt(arr_stdnt, arr_key, num_count_std, MODE_SORT);
        }
        // Вывести не отсортированную структуру
        else if (menu == 7)
        {
            print_stdnt(arr_stdnt, arr_key, num_count_std, MODE_NOSORT);
        }
        //вывод результатов сравнения эффективности работы программы при обработке данных в исходной таблице и в таблице ключей
        else if (menu == 8)
        {
            printf("\n Эффективность работы с ключами составила = %llu%%\n", measured(arr_stdnt, arr_key, num_count_std));
        }
        else if (menu == 9)
        {
            print_table_measure(arr_stdnt, arr_key, num_count_std);
        }
        else if (menu == 10)
        {
            print_info();
        }
    }

    return rc;
}