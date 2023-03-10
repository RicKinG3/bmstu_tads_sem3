#include "../inc/check_f_str.h"
#include "../inc/errors.h"

FILE *check_in_f(int argc, char *argv)
{
    if (argc != 2)
        return NULL;

    FILE *f = fopen(argv, "r+w");
    if (f == NULL)
        return NULL;

    return f;
}

bool check_int(char *num)
{
    for (size_t i = 1; i < strlen(num); i++)
        if (!isdigit(num[i]))
            return true;

    return false;
}

bool is_empty_file(FILE *f)
{
    rewind(f);
    if (feof(f) != 0)
        return true;
    char ch;
    if (fscanf(f, "%c", &ch) != 1)
        return true;
    if (ch == '\n')
        return true;
    rewind(f);

    return false;
}

bool is_normal_file(FILE *f)
{
    rewind(f);
    if (is_empty_file(f))
    {
        puts("!");
        puts("Файл пуст сначала заполните его");
        return false;
    }
    int ch = 0;
    int prec_ch = 1;

    while (!feof(f))
    {
        ch = getc(f);
        // printf("|prev = {%c}|now = {%c}|\n", prec_ch, ch);
        if (ch == '\n' && ch == prec_ch)
        {
            puts("!");
            puts("Файл содержит недопустимые поля");
            return false;
        }
        prec_ch = ch;
    }

    rewind(f);
    return true;
}