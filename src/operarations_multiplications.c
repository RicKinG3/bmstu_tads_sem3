#include "struct.h"
#include "operarations_multiplications.h"
#define N 31

// Массив хранящий информацию о текущем перемноженном разряде
char tmp[N * 2];

// Перемножение разрядов, вспомогательная функция
void disch_multp(char *num1, int len1, char *tmp, int tmp_len, int multp_num)
{
    int disch_numb;
    while (len1 != 0)
    {
       
        disch_numb = multp_num * (num1[--len1] - '0'); // перемножение одной мантисы с оодним числом
        tmp[tmp_len] = (char_to_int(tmp[tmp_len]) + disch_numb % 10) + '0';         //сложение последноних чисел
        tmp[tmp_len - 1] = (char_to_int(tmp[tmp_len - 1]) + disch_numb / 10) + '0'; // сложение передних чисел
        tmp_len--;

    }

}

// Складывание разрядов при умножении, вспомогательна функция при умножении
void disch_sum(char *res, char *tmp, int len)
{
    int disch_numb;
    while (len != 1)
    {
        disch_numb = char_to_int(tmp[len]) + char_to_int(res[len]);
        res[len] = (disch_numb % 10) + '0';
        res[len - 1] = (char_to_int(res[len - 1]) + disch_numb / 10) + '0';
        len--;
    }
}

// Перемножение мантисс
void multp_mantissa(char *num1, int len1, char *num2, int len2, char *mantissa, int disch)
{
    int tmp_len = (N * 2 - disch);
    memset(tmp, '0', sizeof(tmp));

    while (len2 > -1)
    {
        tmp_len = (N * 2 - disch);
        memset(tmp, '0', sizeof(tmp));
        disch_multp(num1, len1, tmp, tmp_len, char_to_int(num2[len2]));
        disch_sum(mantissa, tmp, (N * 2) - 1);

        len2--;
        disch++;
    }

    mantissa[N * N] = '\0';
 
}
// Функция перемножения целого и действительного числа
int multp(number_t *num1, number_t *num2, number_t *result)
{
    multp_mantissa(num1->mantissa, strlen(num1->mantissa), num2->mantissa, strlen(num2->mantissa) - 1, result->mantissa, 1);
    sign_defin(num1, num2, result);
    point_defin(num1, num2, result);

    return PASS;
}

void normalize(number_t *num)
{
    int k = 0;
    int len = strlen(num->mantissa);
    int i = len - num->point_ind;

    while (num->mantissa[i++] == '0' && i < len)
        ++k;

    if (k == 0)
        return;

    num->degree -= k;

    for (int q = len - 1; q > k; q--)
    {
        num->mantissa[q - k] = num->mantissa[q];
        num->mantissa[q] = '\0';
    }
    num->point_ind -= k;
}

// Функция превращающая char в int
int char_to_int(char symb)
{
    return symb - '0';
}

// Нахождение точки у результата
void point_defin(number_t *num1, number_t *num2, number_t *result)
{
    result->point_ind = num1->point_ind + num2->point_ind;
}

// Приведение числа к экспоненциальному виду
void reduction_to_exp(char *num)
{
    int len = strlen(num);

    num[len++] = 'E';
    num[len++] = '+';
    num[len] = '0';
}

// Определение знака у мантиссы действительного числа
void sign_defin(number_t *num1, number_t *num2, number_t *result)
{
    if (num1->mantissa_sign == num2->mantissa_sign)
        result->mantissa_sign = '+';
    else
        result->mantissa_sign = '-';
}

// Функция, проверяющая, записано число в экспоненциальном виде или нет
bool check_exp(char *num, size_t cur_len, size_t len)
{
    if (cur_len == len)
        return true;

    if (toupper(num[cur_len]) == 'E')
        return false;

    return check_exp(num, ++cur_len, len);
}

// функция округления числа
void rounding(number_t *numb, int end_ind, int flag)
{
    int int_numb = numb->mantissa[end_ind + 1] - '0';
    int int_numb_cur = numb->mantissa[end_ind] - '0';

    if (flag)
        numb->mantissa[end_ind] = ((int_numb_cur + 1) % 10) + '0';

    if (numb->mantissa[end_ind + 1] >= '5')
        numb->mantissa[end_ind] = ((int_numb + 1) % 10) + '0';

    if (numb->mantissa[end_ind] == '0' && end_ind != 0)
        rounding(numb, --end_ind, 1);
}

void null_rounding(number_t *numb, size_t ind)
{
    while (ind != 0)
    {
        if (numb->mantissa[ind] == '0')
            numb->mantissa[ind] = '\0';
        ind--;
    }
}

void add_null(char *arr)
{
    int len = strlen(arr);

    for (int i = len - 1; i > 0; i--)
        arr[i + 1] = arr[i];
}
