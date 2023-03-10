#include "../inc/io_menu.h"

void flush_input(void)
{
    char c;
    while ((scanf("%c", &c) == 1) && (c != '\n'))
        ;
}

size_t read_line(char *s, size_t n, FILE *f)

{
    int ch;
    size_t i = 0;
    while ((ch = fgetc(f)) != '\n' && ch != '\0' && ch != EOF)
        if (i < n - 1)
        {
            if (isalpha(ch))
                return ERR_STR_READ;
            s[i++] = ch;
        }
            
    s[i] = '\0';
    if (i == 0 || s[0] == '\n')
        return ERR_STR_READ;
    return PASS;
}

bool check_int(char *num)
{
    for (size_t i = 1; i < strlen(num); i++)
        if (!isdigit(num[i]))
            return true;

    return false;
}

#define ERR_UNRIGHT_LIST_MAX_LEN -2

int input_max_len_stack(int *max_len)
{
    int rc = PASS;
    puts("\nВведите размер стека (кол-во элементов ∈ [1, 10000]:");
    rc = input_int(max_len);

    if ((rc != PASS) || (*max_len < 0) || (*max_len > 10000))
    {
        puts("\nОшибка: размер стека это целое число, ∈ [1, 10000]\n");
        return ERR_UNRIGHT_LIST_MAX_LEN;
    }
    return PASS;
}

int input_int(int *num)
{
    char str[MAX_MENU_ITEM_LEN] = {0};

    if (read_line(str, MAX_MENU_ITEM_LEN, stdin) != PASS)
        return ERR_READ_ACTION;
    if (check_int(str))
        return ERR_WRONG_ACTION;
    int num_tmp = atoi(str);
    *num = (int)num_tmp;

    return PASS;
}

int choose_action(int *action)
{
    char str[MAX_MENU_ITEM_LEN] = {0};

    if (read_line(str, MAX_MENU_ITEM_LEN, stdin) != PASS)
        return ERR_READ_ACTION;

    if (check_int(str))
        return ERR_WRONG_ACTION;
    int menu = atoi(str);

    if (menu < 0 || menu > 13)
        return ERR_WRONG_ACTION;

    *action = (int)menu;

    return PASS;
}

void print_menu(void)
{
    printf("\n  ||| Меню ||| \n \
        \n||| Стек в виде массива:\n \
        1. Записать несколько элементов в стек\n \
        2. Добавить один элемент в стек\n \
        3. Удалить элемент из стека\n \
        4. Вывести текущее состояние стека\n \
        5. Произвести вычисление и вывести результат на экран\n\n \
        6. Вывести замеры времени и памяти \
        \n\n||| Стек в виде списка:\n \
        7.  Записать несколько элементов в стек\n \
        8.  Добавить один элемент в стек\n \
        9.  Удалить элемент из стека\n \
        10. Вывести текущее состояние стека\n \
        11. Произвести вычисление и вывести результат на экран\n \
        12. Распечатать массив освободившихся адрессов\n \
        13. Вывести инфо\n \
    \n0.  Выйти из программы \n");

    printf("Введите пункт меню целое ∈  [0 ; 12] : ");
}
void print_info(void)
{
    printf("\n  ||| ИНФО ||| \n \
        1. Для заполнения стека используйте целочисленые значения\n \
        2. Для указания размеров стека и кол-во эл используйте целочисленые значения\n \
        3. Вы не сможете удалить/вывести из/ стека эл, если стек пуст\n \
        4. При вводе выражения не используйте пробел, используйте только целочисленные числа\n \
        5. В выражение первый и последний символ число\n\
        6. В выражение не возможно указать две операции\n\
        7.  Вы не сможете добавить эл в стек если размер стека = кол-ву эл в нем\n");
}