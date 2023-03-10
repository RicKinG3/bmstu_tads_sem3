#include <stdio.h>

#include "menu.h"
#include "func.h"
#include "errors.h"
#include "mtr.h"
#include "mtres_actions.h"
#include "check_str.h"

void print_menu(void)
{
    puts("");
    puts("|||  МЕНЮ  |||");
    puts("");
    puts("1)  - Ввести вектор-строку и матрицу вручную");
    puts("2)  - Сгенерировать вектор-строку и матрицу по проценту заполненности");
    puts("3)  - Вывести исходную матрицу и вектор-строку");
    puts("4)  - Перемножить матрицы алгоритмом обработки разреженных матриц");
    puts("5)  - Перемножить матрицы стандартным алгоритмом обработки матриц");
    puts("6)  - Вывести таблицу эффективности");
    puts("7)  - Вывести информацию");
    puts("0)  - Выход");
    puts("");
}

void print_info(void)
{
    puts("");
    puts("|||  INFO  |||");
    puts("");
    puts("1)  - Для выбора меню используйте целые числа от 0 до 7");
    puts("2)  - При заполнение матрицы используйте целые числа");
    puts("3)  - Возможен ввод пустых матриц, но не их генерация");
    puts("4)  - Размер вектор-строки должен  соответствовать кол-ву строк в исходной матрице");
    puts("5)  - Размер строк и столбцов должно положительным");

    puts("");
}

void print_error_message(int code)
{
    if (ERR_WRONG_ACTION == code)
    {
        printf("\n ВВеденное число не соответствует ни одному действию код ошибки =  %d\n", code);
        puts("Попробуйте ещё раз.\n");
    }
    else if (ERR_READ_ACTION == code)
    {
        printf("\nnОШИБКА Некорректный ввод, код ошибки =  %d\n", code);
        printf("Попробуйте ещё раз.\n");
    }
    else if (ERR_TOO_MUCH_NONZERO == code)
        printf("\nnОШИБКА Количество ненулевых элементов больше количества элементов в матрице код ошибки =  %d\n", code);
    else if (ERR_NONINTEGER == code)
        printf("\nОшибка при чтении числа, код ошибки =  %d\n", code);
    else if (ERR_NONROW == code)
        printf("\nnОШИБКА Первая матрица не является вектором-строкой, код ошибки =  %d\n ", code);
    else if (ERR_WRONG_ELEMENT_PARAMETERS == code)
        printf("\nnОШИБКА Заданы Неверные  параметры элемента матрицы, код ошибки =  %d\n ", code);
    else if (ERR_EMPTY_MTR == code)
        printf("\nnОШИБКА При заполнение матриц одна из матриц пустая, код ошибки =  %d\n ", code);
    else if (ERR_NO_MTR == code)
        printf("\nnОШИБКА Для начала введите или сгенерируйте матрицы, код ошибки =  %d\n ", code);
    else if (ERR_PRINT_FLAG_READ == code)
        printf("\nОШИБКА Такого значения нет в списке, код ошибки =  %d\n ", code);
    else if (ERR_TOO_MUCH_NONZERO == code)
        printf("\nnОШИБКА Количество ненулевых элементов больше количества элементов в матрице код ошибки =  %d\n", code);
    else if (ERR_WRONG_PERCENT == code)
        printf("\nОШИБКА Процент -- целое число от 0 до 100, код ошибки =  %d\n ", code);
    else if (ERR_NONUINTEGER == code)
        printf("\nnОШИБКА Введенное значение выходит за допустимый диапазон значений , код ошибки =  %d\n", code);
    else if (ERR_MEMORY_ALLOCATION == code)
        printf("\nОшибка выделения памяти, код ошибки =  %d\n ", code);
    else if (ERR_WRONG_mtrES_SIZES == code)
        printf("\nnОШИБКА Умножение невозможно из-за неверных размер матриц, код ошибки =  %d\n ", code);
    else if (ERR_NONINTEGER == code)
        printf("\nОшибка при чтении числа, код ошибки =  %d\n", code);
    else if (ERR_NONROW == code)
        printf("\nnОШИБКА Первая матрица не является вектором-строкой, код ошибки =  %d\n ", code);
    else if (ERR_WRONG_ELEMENT_PARAMETERS == code)
        printf("\nnОШИБКА Заданы Неверные  параметры элемента матрицы, код ошибки =  %d\n ", code);
}

int choose_action(int *action)
{
    puts("Введите целое число от 0 до 7, для выбора меню:  ");

    char str[MAX_MENU_ITEM_LEN] = {0};

    if (read_line(str, MAX_MENU_ITEM_LEN, stdin) != PASS)
        return ERR_READ_ACTION;

    if (check_int(str))
        return ERR_WRONG_ACTION;
    int menu = atoi(str);

    if (menu < 0 || menu > 7)
        return ERR_WRONG_ACTION;

    *action = (int)menu;

    return READ_OK;
}

int do_action(int action,
              sparse_mtr_t *sparse_mtr,
              sparse_mtr_t *sparse_row,
              mtr_t *mtr,
              mtr_t *row)
{
    int rc = MTR_OK;
    int tmp;
    if (action == 1)
        rc = read_mtres(sparse_mtr, sparse_row, mtr, row);
    else if (action == 2)
        rc = generate_mtres(sparse_mtr, sparse_row, mtr, row);
    else if (action == 3)
        rc = user_print(mtr, row, sparse_mtr, sparse_row);
    else if (action == 4)
        rc = sparse_multiply_row_and_mtr(sparse_row, sparse_mtr, MODE_PRINT, &tmp);
    else if (action == 5)
        rc = multiply_row_and_mtr(row, mtr, MODE_NOT_PRINT, &tmp);
    else if (action == 6)
        print_table_measure(sparse_row, sparse_mtr, row, mtr);
    else if (action == 7)
        print_info();
    else
    {
        free_mtr_t(mtr);
        free_mtr_t(row);
        free_sparse_t(sparse_mtr);
        free_sparse_t(sparse_row);
        exit(EXIT_SUCCESS);
    }

    return rc;
}