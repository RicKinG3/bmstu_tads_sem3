#include "../inc/separation.h"

int check_operation(char sym)
{
    if ((sym == '+') || (sym == '-') || (sym == '*') || (sym == '/'))
    {
        return RIGHT_OPERATION;
    }
    else
    {
        return UNRIGHNT_SYMBOL;
    }
}

int read_num_from_arr_char(char *sym, int *ind)
{
    // printf("@@@ index for translate = %d @@@", *ind);
    char num[150];
    int i = 0;

    while ((sym[*ind] >= '0') && (sym[*ind] <= '9'))
    {
        num[i] = sym[*ind];
        i++;
        *ind += 1;
    }

    num[i] = '\0';

    int number;
    sscanf(num, "%d", &number);

    return number;
}

int translate_operation(char sym)
{
    if (sym == '+')
    {
        return 1;
    }
    else if (sym == '-')
    {
        return 2;
    }
    else if (sym == '*')
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

int check_priority(int sym)
{
    if ((sym == 1) || (sym == 2))
    {
        return 1;
    }

    return 2;
}
#include <ctype.h>
int read_expression(expres_t *expression)
{

    puts("\nВведите выражение в следующем формате без пробелов :\nчисло|знак|...число|знак|число \
        \nДоступные операции: (+) сложение;  (-) вычитание; (*) умножение; (/) деление \n");

    char sym;
    int rc, i = 0;

    scanf("%c", &sym);
    if (isalpha(sym))
    {
        puts("Ошибка: неверный символ в выражении");
        return ERR_WRONG_SYMBOL;
    }
    expression->sym[i] = sym;
    i++;

    while (((rc = scanf("%c", &sym)) == 1) && (sym != '\n'))
    {
        if (isalpha(sym))
        {
            puts("Ошибка: неверный символ в выражении");
            return ERR_WRONG_SYMBOL;
        }
        if ((sym > '9') || (sym < '0')) // || (sym != '+') || (sym != '-'))
        {
            if (!check_operation(sym))
            {
                puts("Ошибка: неверный символ в выражении");
                return ERR_WRONG_SYMBOL;
            }
        }

        if (check_operation(sym))
        {
            if ((expression->sym[i - 1] == '+') || (expression->sym[i - 1] == '-'))
            {
                puts("Ошибка: не может быть введено несколько знаков подряд");
                return ERR_WRONG_SYMBOL;
            }
        }

        expression->sym[i] = sym;
        i++;
    }

    expression->sym[i] = '\0';
    expression->sym[i] = '\0';

    if (check_operation(expression->sym[0]))
    {
        puts("Ошибка: первым должно быть введено число");
        return ERR_FIRST_SYM_NOT_NUM;
    }

    if (check_operation(expression->sym[i - 1]))
    {
        puts("Ошибка: последним должно быть введено число");
        return ERR_LAST_SYM_NOT_NUM;
    }

    printf("\n\nВеденное выражение: %s\n\n", expression->sym);

    expression->len = i;

    return OK_READ_EXPRESSION;
}