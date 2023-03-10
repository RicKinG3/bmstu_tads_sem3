#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "readme.h"
#include <stdbool.h>

/**
@function read_int
@brief обработка входного числа инт
@param[in] number_int структура
@param[in] number – входная строка с ожидающим числом инт
@return Код ошибки
*/

int read_int(number *number_int, char *number)
{
    bool is_null = false;

    number_int->len = 0; // инициализируем структуру для долбнейшей обработок ощибок
    number_int->after_dot_len = 0;
    number_int->order = 0;

    if ((number[0] == '+' || number[0] == '-') && isdigit(number[1])) // если есть первый знак и после число
    {
        number_int->sign = number[0];
        if (number[1] == '0' && number[2] == '\n') // для обработки нуля со знаком
        {
            is_null = true;
            number_int->number[0] = '0';
        }
        else if (number[1] == '0' && number[2] != '\n') // +000 error
            return ERR_INPUT;
    }
    else if (number[0] >= '1' && number[0] <= '9')
    {
        number_int->sign = '+';
        number_int->len++;
        number_int->number[0] = number[0];
    }
    else if (number[0] == '0' && number[1] == '\n') // для обработки нуля без знакак
    {
        is_null = true;
        number_int->number[0] = '0';
        number_int->sign = '+';
        number_int->len++;
    }
    else
        return ERR_INPUT;

    int i = 1;
    char c = number[i];

    if (!is_null)
        while (c != '\0' && c != '\n' && number_int->len < LEN) // цикл для обработки входной строки содержащая инт
        {
            if (isdigit(c)) // ессли с число то добавляем в массив иначе ошибка
            {
                number_int->number[number_int->len++] = c;
                c = number[++i];
            }
            else
                return ERR_INPUT; // добавить ошибку для инта
        }

    if (c != '\0' && c != '\n' && !is_null) // если с не конец строки то число больше 30 символов
        return ERR_INPUT;

    number_int->order = number_int->len; // длина мантисы   но в порядке для экономии(?)

    return PASS;
}

/**
@function read_flt
@brief обработка входного действительного числа
@param[in] number_flt структура
@param[in] number – входная строка с ожидающим действительным числом
@return Код ошибки
*/
// E 0E13

#define ERR_LEN 4
#define E "E"
#define START 0
#define ERR_FLT 789

int is_null(char *s, int pos)
{
    for (; s[pos] == '0'; pos++)
        printf("%c", s[pos]);

    return pos;
}

bool is_sign(char ch)
{
    return (ch == '+' || ch == '-') ? true : false;
}

bool is_space(char ch)
{
    return (ch == ' ') ? true : false;
}

bool is_dot(char ch)
{
    return (ch == '.') ? true : false;
}

bool is_e(char ch)
{
    return (ch == 'E') ? true : false;
}

bool is_strend(char ch)
{
    return (ch == '\0' || ch == '\n') ? true : false;
}

size_t put_num_in_struct(number *numstruct, char *strnum)
{
    int i = 0;
    while (isdigit(strnum[i]) && *strnum)
    {
        if (numstruct->len > LEN)
            return ERR_LEN;
        numstruct->number[numstruct->len++] = strnum[i++];
    }
    i++;
    printf("%c ___ %d____", strnum[i], i);
    if (is_space(strnum[i]) || is_strend(strnum[i]))
        i--;
    i--;
    return i;
}

int read_flt(number *number_flt, char *strnumber)
{
    bool fl_e = false;
    bool fl_dot = false;
    bool fl_null = false;

    number_flt->len = 0;
    number_flt->sign = '+';
    number_flt->order = 0;
    number_flt->after_dot_len = 0;

    int lenstr = strlen(strnumber);
    int i = 0;
    if (lenstr > LEN || lenstr < 1)
        return ERR_LEN;
    // mantisa

    char *porder = strtok(strnumber, E);
    char *pmantis = porder; // SAVE mantis
    porder = strtok(NULL, E);

    if (porder != NULL) //  E
        fl_e = true;

    if (fl_e)
        puts("E");
    int lenmantis = strlen(pmantis);
    // manris

    if (is_sign(pmantis[i]))
    {

        number_flt->sign = pmantis[i++];
        //+ 0.00000 E + 789
        if (is_space(pmantis[i]))
        {
            i++;
        }

        // возвращает +1 от позиции с которой начал значит до нули
        if (is_null(pmantis, i) == i + 1) // check for first null| если стоит 0{число точка или нуль то ошибка}
        {
            i++;
            // null
            number_flt->number[0] = '0';
            number_flt->len++;
            if (is_dot(pmantis[i]))
            {
                i++;
                fl_dot = true;
                if (is_strend(pmantis[lenmantis - 1]))
                    lenmantis--;
                printf("|%s|", pmantis);
                printf("<%d___%d >         ", is_null(pmantis, i), lenmantis);
                if (is_null(pmantis, i) == lenmantis - 1) //+ 0.0000000 E 123 -3 (dot + plus and index)
                {

                    i = is_null(pmantis, i);

                    if ((is_strend(pmantis[i]) || is_space(pmantis[i])))
                        fl_null = true;
                    else
                        return ERR_FLT;
                }
                else //+ 0.0002E45 // обработка после точки
                {
                    char *afterdot = strtok(pmantis, ".");
                    afterdot = strtok(NULL, ".");
                    puts(afterdot);
                    printf("((%ld___%ld", put_num_in_struct(number_flt, afterdot), strlen(afterdot));

                    // if (put_num_in_struct(number_flt, afterdot) != strlen(afterdot)) // возращает количество записаных чисел в структуру
                    //    return ERR_FLT;
                    /*
                 while (number_flt->number[0] == '0')
                 {
                     for (int j = 0; j < number_flt->len; j++)          ВЫДЕЛИТЬ ФУНКЦИЮ ДЛЯ ЭТОЙ ХНИ
                         number_flt->number[j] = number_flt->number[j + 1];
                     number_flt->len--;
                 }
                 number_flt->order += (number_flt->len - number_flt->after_dot_len);*/
                }
            }
            else
                return ERR_FLT;
        }
        else
            return ERR_FLT;
    }
    // not sign
    else
    {
        // if first null
        if (is_null(pmantis, i) == i + 1)
        {
            number_flt->number[0] = '0';
            number_flt->len++;
            i++;

            if (is_dot(pmantis[i]))
            {
                i++;
                fl_dot = true;
                if (is_null(pmantis, i) == lenmantis - 3) //+ 0.0000000 E 123 -3 (dot + plus and index)
                {

                    i = is_null(pmantis, i);

                    if (fl_e && (is_strend(pmantis[i]) || is_space(pmantis[i])))
                        fl_null = true;
                    else
                        return ERR_FLT;
                }
            }
        }
    }

    if (fl_dot && fl_null)
        puts("is tir");

    return PASS;
}