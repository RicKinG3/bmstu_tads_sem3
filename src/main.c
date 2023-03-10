#include "struct.h"
#include "print_res.h"
#include "data_check.h"
#include "parsing.h"
#include "operarations_multiplications.h"

#define N 100
#define MAX_LEN 30


size_t read_line(char *s, size_t n)
{
    int ch;
    size_t i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
        if (i < n - 1)
            s[i++] = ch;
    s[i] = '\0';
    if (i == 0 || s[0] == '\n')
        return READ_ERROR;
    return PASS;
}


int main(void)
{
    printf("Смоделировать операцию умножения действительного числа на целое число.\n\
        Правила ввода:\n\
    \nПРИМЕР ДЕЙСТВИТЕЛЬНОГО ЧИСЛА: [знак]m.nЕ[знак]K;\n\
    1) Действительное число вводится обязательно с одним знаком в начале числа;\n\
    2) Порядок действительного числа вводится с одним знаком;\n\
    3) Суммарная длина мантиссы ( сумма m и n ) не должна превышать тридцати цифр;\n\
    4) Величина порядка ( К ) не должна превышать пяти цифр;\n\
    6) Действительное число может быть записано либо в экспоненциальном формате ( E либо е ) - латинские, либо иметь одну точку, либо не иметь точку;\n\
    7) В записи числа не должно быть пробелов и других символов отличающихся от выше перечисленных;\n\
    \nПРИМЕР ЦЕЛОГО ЧИСЛА: [знак]d;\n\
    8) Длина целого числа должна быть до тридцати десятичных цифр;\n\
    9) Целое число может иметь только один знак в начале числа;\n\
    10) После знака не ставится пробел;\n\
    11) Каждое число вводится на отдельной строке;\n");

    printf("\n%57s %25s\n", "мантисса", "степень");
    printf("%32d %8d %9d %9d %2d %3d\n", 1, 10, 20, 30, 1, 5);
    printf("%71s", "±|--------|---------|---------|E±|---|\n");

    // Инициализация структур и массивов
    char real_num[N] = {0};
    char int_num[N] = {0};
    number_t real_num_parsed, int_num_parsed, result;
    memset(result.mantissa, '0', sizeof(result.mantissa));

    printf("Введите действительное число: ");
 
    // Считывание и проверка первого (действительного) числа
    if (read_line(real_num, sizeof(real_num)) == READ_ERROR)
    {
         printf("Ошибка: действительное число введено некорректно!\n");
        return READ_ERROR;
    }

    // Приведение числа к эспоненциальному виду, если оно еще не приведено
    if (check_exp(real_num, 0, strlen(real_num)))
        reduction_to_exp(real_num);

    // Обработка ошибок
    int rc = check_real(real_num);

    if (rc)
    {
        if (rc == NO_SIGN)
        {
            printf("Ошибка: не указан знак мантиссы!\n");
            return NO_SIGN;
        }

        if (rc == NO_DEGREE_SIGN)
        {
            printf("Ошибка: не указан знак степени!\n");
            return NO_DEGREE_SIGN;
        }

        printf("Ошибка: дейтсвительное число введено в некорректной форме!\n");
        return INVALID_DATA;
    }

    // помещаем действительное число в структуру
    rc = parsing(real_num, &real_num_parsed);

    if (rc == RANGE_ERR_MNT)
    {
        printf("Ошибка: мантисса должна содержать менее 30 цифр!\n");
        return RANGE_ERR_MNT;
    }

    if (rc == RANGE_ERR)
    {
        printf("Ошибка: степень должна состоять из 5 или менее символов!\n");
        return RANGE_ERR;
    }

    if (!real_num_parsed.mantissa[0])
    {
        printf("Ошибка: некорректный ввод!\n");
        return INVALID_DATA;
    }
    if (real_num[1] == '.')
        add_null(real_num);

    bool is_first_null = false;

    if (real_num[1] == '0' && real_num[2] == '.')
    {
        is_first_null = true;
        normalize(&real_num_parsed);
    }
    printf("Введите целое число: ");
    printf("         ");
    // Считывание и проверка второго (целого) числа
    if (read_line(int_num, sizeof(int_num)) == READ_ERROR)
    {
        printf("Ошибка: целое число введено некоректно!\n");
        return READ_ERROR;
    
    }
    if (check_int(int_num))
    {
        printf("Ошибка: целое число введено в некорректной форме!\n");
        return INVALID_DATA;
    }

    // Приведение числа к экспоненциальному виду, если оно еще не привидено
    if (check_exp(int_num, 0, strlen(int_num)))
        reduction_to_exp(int_num);

    // Помещаем целое числа в структуру
    rc = parsing(int_num, &int_num_parsed);
    if (rc == RANGE_ERR_MNT)
    {
        printf("Ошибка: целое число должно содержать менее 30 цифр!\n");
        return RANGE_ERR_MNT;
    }

    if (rc == RANGE_ERR)
    {
        printf("Ошибка: степень должна содержать 5 или менее цифр!\n");
        return RANGE_ERR;
    }

    if (!int_num_parsed.mantissa[0])
    {
        printf("Ошибка: некорректный ввод!\n");
        return INVALID_DATA;
    }

    int i = 0, sum = 0; // небольшая проверка на нули 
    bool is_null = false;

    while (real_num_parsed.mantissa[i])
        sum += (real_num_parsed.mantissa[i++] -'0');

    if (sum == 0 || int_num_parsed.mantissa[0] == '0')
        is_null = true;
    else
    {
        // Перемножение  чисел
        multp(&real_num_parsed, &int_num_parsed, &result);
        // Приведение результата к финальному виду и обработка ошибок
        rc = final_parsing(real_num_parsed, int_num_parsed, &result, is_first_null);

        if (rc == RANGE_ERR_MNT)
        {
            printf("Предупреждение: результат мантиссы более, чем 30 символов, поэтому он был округлен до 30 знаков!\n");
            rounding(&result, MAX_LEN - 2, 0);
            result.mantissa[29] = '\0';
        }

        if (rc == RANGE_ERR)
        {
            printf("Ошибка: результат степени состоит более чем из 5 символов!\n");
            return RANGE_ERR_MNT;
        }

    }

    print_result(result, is_null);
    return OK;
}