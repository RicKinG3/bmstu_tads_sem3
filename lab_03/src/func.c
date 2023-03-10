#include <string.h>
#include <stdio.h>
#include <limits.h>

#include "func.h"
#include "errors.h"

size_t my_strlen(  char *  str)
{
    size_t count = 0;
    size_t len = 0;

    while (str[count] != '\0')
    {
        len++;
        count++;

        if (str[count] < 0 || str[count] > 127)
            count++;
    }

    return len;
}

int read_str(char *  str,   int max_len, FILE *stream)
{
    if (!fgets(str, max_len, stream))
        return ERR_FGETS;

    size_t byte_len = strlen(str);

    if ('\n' == str[byte_len - 1])
        str[byte_len - 1] = '\0';
    else
    {
        clear_stdin();
        return ERR_STR_READ;
    }

    return READ_OK;
}

void clear_stdin(void)
{
    char ch;
    do
    {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

int read_int(int *  unint)
{
    long long int llint;

    if (scanf("%lld", &llint) != 1)
        return ERR_NONINTEGER;

    if (llint < 0 || llint > UINT_MAX)
        return ERR_NONUINTEGER;

    *unint = (int) llint;

    return MTR_OK;
}

int my_round(double number)
{
    if (number < 0)
        number = - number;

    double frac = number - (int) number;

    if (frac < 0.5)
        return (int) number;
    else
        return (int) number + 1;
}
