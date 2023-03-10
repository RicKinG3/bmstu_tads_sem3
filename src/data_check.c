#include "data_check.h"

// Массив c разрешенных символов
char allowed_symb[N_ALLOWED_SIG] = {'-', '.', '+', 'e', 'E'};

// Проверка числа на допустимые символы
int check_allowed(char symb, int i, int not_allowed_cnt)
{
    if (symb != allowed_symb[i] && (symb < '0' || symb > '9'))
        ++not_allowed_cnt;

    if (i < (N_ALLOWED_SIG - 1))
        return check_allowed(symb, ++i, not_allowed_cnt);

    if (not_allowed_cnt != N_ALLOWED_SIG)
        return PASS;

    return INVALID_DATA;
}

// Проверка, что у степени есть знак
int is_sign_after_exp(char *num, size_t i)
{
    if (toupper(num[i]) == 'E')
        if (num[++i] != '-' && num[i] != '+')
            return NO_DEGREE_SIGN;

    return PASS;
}

bool check_int(char *num)
{
    for (size_t i = 1; i < strlen(num); i++)
        if (!isdigit(num[i]))
            return true;

    return false;
}

// Проверка, что знак находится в нужном месте
int check_pos_sign_and_exp(char *num, size_t i)
{
    if (num[i] == '+' || num[i] == '-')
    {
        if (i == 0)
            return PASS;
        if (toupper(num[i - 1]) == 'E')
            return PASS;

        return INVALID_DATA;
    }

    return PASS;
}

// Проверка, что в строке находится только лишь один символ Е
int is_one_e(char symb, int *e_cnt)
{
    if (toupper(symb) == 'E')
        ++(*e_cnt);

    if (*e_cnt > MAX_E)
        return INVALID_DATA;

    return PASS;
}

// Проверка, что в степени нет точки
int check_point_in_degree(char *num, size_t i, int *e_cnt)
{
    if (!(*e_cnt) && num[i] == '.')
        return INVALID_DATA;

    return PASS;
}

// провекрка что в числе одна точка
int is_one_point(char *num, int i, int *point_cnt)
{
    while (num[i])
    {
        if (num[i] == '.')
            (*point_cnt)++;

        if ((*point_cnt) > 1)
            return INVALID_DATA;
        i++;
    }

    return PASS;
}

// Функция проверяющая наличие знака перед числом
int check_sign(char *num)
{
    if (num[0] != '+' && num[0] != '-')
        return NO_SIGN;

    return PASS;
}

// Вспомогательная функция, рекурсивно проверяющая допустимые символы и знаки в строке
int check_num(char *num, size_t len, int *e_cnt)
{
    while (len != 0)
    {
        if (check_allowed(num[len], 0, 0))
            return INVALID_DATA;
            
        if (is_one_e(num[len], e_cnt))
            return INVALID_DATA;

        if (check_pos_sign_and_exp(num, len))
            return INVALID_DATA;

        if (is_sign_after_exp(num, len))
            return NO_DEGREE_SIGN;

        if (check_point_in_degree(num, len, e_cnt))
            return INVALID_DATA;

        len--;
    }

    return PASS;
}

// Функция проверяющая действительное число на корректность
int check_real(char *num)
{
    int e_cnt = 0;
    int point_cnt = 0;
    size_t len = strlen(num) - 1; // взятие индекса последнего элемента в массиве num

    int code_err = check_num(num, len, &e_cnt);

    if (code_err)
    {
        if (code_err == NO_DEGREE_SIGN)
            return NO_DEGREE_SIGN;
        
        return INVALID_DATA;
    }
       
    if (check_sign(num))
        return NO_SIGN;

    if (toupper(num[len]) == 'E')
        return INVALID_DATA;

    if (num[len] == '+' || num[len] == '-')
        return INVALID_DATA;
   
    if (is_one_point(num, 0, &point_cnt))
        return INVALID_DATA;
 
    return PASS;
}