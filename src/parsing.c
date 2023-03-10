#include "parsing.h"
#include "operarations_multiplications.h"
#include "struct.h"

// Вспомогательная функция
void null_counter(char *fin_mantissa, int len, int *null_cnt, bool back_flag)
{
    while (fin_mantissa[len] == '0')
    {
        ++(*null_cnt);
        if (back_flag)
            --len;
        else
            ++len;
    }
}

bool null_check(number_t *num1, int len)
{
    for (int i = 0; i < len; i++)
        if (num1->mantissa[i] != '0')
            return false;

    return true;
}

// Поиск индекса степени
void find_degree(number_t *result, int ind)
{
    while (1)
    {
        if (result->mantissa[ind] == '+' || result->mantissa[ind] == '-')
        {
            result->mantissa[ind] = '\0';
            break;
        }
        ++ind;
    }
}

int add_degree_p(number_t num)
{
    int len = strlen(num.mantissa) - 1;
    int count_null = 0;

    while (num.mantissa[len] == '0' && len)
    {
        ++count_null;
        --len;
    }

    return count_null;
}

// Проверка знака у мантиссы
void sign_check(char *num, number_t *num_parsed, int *ind)
{
    if (!isdigit(num[*ind]))
    {
        num_parsed->mantissa_sign = num[*ind];
        ++(*ind);
    }
}

// Заполнение структуры дефолтными значениями
void std_data(number_t *num_parsed)
{
    memset(num_parsed->mantissa, '\0', sizeof(num_parsed->mantissa));
    num_parsed->degree = 0;
    num_parsed->mantissa_sign = '+';
    num_parsed->point_ind = 0;
}

// Главная функция, запускающая парсинг числа
int parsing(char *num, number_t *num_parsed)
{
    char temp_degree[MAX_DEGREE_CN] = {'\0'};
    std_data(num_parsed);

    int degree_ind = 0;
    sign_check(num, num_parsed, &degree_ind);

    if (parsing_mantissa(num, num_parsed, &degree_ind))
        return RANGE_ERR_MNT;

    if (parsing_degree(num, num_parsed, &degree_ind, temp_degree, 0))

        return RANGE_ERR;

    return PASS;
}

// Парсинг степени
int parsing_degree(char *num, number_t *num_parsed, int *ind, char *temp_degree, int len)
{
    int index = *ind;
    while (1)
    {
        index = *ind;
        if (num[index] == '\0')
        {
            temp_degree[len] = '\0';
            num_parsed->degree = atoi(temp_degree);
            return PASS;
        }

        if (abs(len) > (MAX_DEGREE - 1))
        {
            if (isdigit(temp_degree[0]))
                return PASS;

            return RANGE_ERR;
        }

        temp_degree[len] = num[index];

        ++(*ind);
        ++len;
    }

    return PASS;
}

// Парсинг мантиссы
int parsing_mantissa(char *num, number_t *num_parsed, int *ind)
{
    int index = *ind;
    int len = strlen(num_parsed->mantissa);

    while (1)
    {
        index = *ind;
        len = strlen(num_parsed->mantissa);
        if (num[index] == '.')
        {
            num_parsed->point_ind = index;
            ++(*ind);
        }
        else
        {

            if (toupper(num[index]) == 'E')
            {
                if (num_parsed->point_ind)
                    num_parsed->point_ind = index - num_parsed->point_ind - 1;
                ++(*ind);
                num_parsed->mantissa[len] = '\0';

                return PASS;
            }

            if (len >= MAX_MANTISSA - 1)
                return RANGE_ERR_MNT;

            num_parsed->mantissa[len] = num[index];
            ++(*ind);
        }
    }

    return PASS;
}
char *my_strcpy(char *destination, const char *source)
{
    if (destination == NULL)
        return NULL;

    char *ptr = destination;

    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
    
    return ptr;
}

// Финальный парсинг и обработка числа (уже в структуре)
int final_parsing(number_t num1, number_t num2, number_t *result, bool fl)
{
    int null_cnt_behind = 0;
    int null_cnt_front = 0;
    int len = strlen(result->mantissa);

    find_degree(result, 0);

    null_counter(result->mantissa, len - 1, &null_cnt_behind, true);
    null_counter(result->mantissa, 0, &null_cnt_front, false);

    result->mantissa[len - null_cnt_behind] = '\0';
    my_strcpy(result->mantissa, (result->mantissa + null_cnt_front));


    null_cnt_behind = (fl) ? add_degree_p(num2) : null_cnt_behind;
    result->degree = num1.degree + null_cnt_behind + ((int)(strlen(result->mantissa)) - result->point_ind);
    if(num2.mantissa[0] == '1' &&  strlen(num2.mantissa) == 1 && (result->degree > 1000 || (result->degree < -1000 ) ) )
        result->degree = num1.degree + null_cnt_behind - result->point_ind;
    if(num2.mantissa[0] == '-' && num2.mantissa[1] == '1' &&  strlen(num2.mantissa) == 2 && (result->degree > 1000 || (result->degree < -1000 ) ) )
        result->degree = num1.degree + null_cnt_behind - result->point_ind;

    if (null_check(result, strlen(result->mantissa)))
        return PASS;

    if (strlen(result->mantissa) == 60)
        result->mantissa[59] = '0';

    if (abs(result->degree) > MAX_DEGREE_SZ)
        return RANGE_ERR;


    if (strlen(result->mantissa) > (MAX_MANTISSA - 1))
        return RANGE_ERR_MNT;

    return PASS;
}