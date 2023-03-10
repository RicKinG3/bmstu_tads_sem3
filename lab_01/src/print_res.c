#include "print_res.h"
#include "struct.h"

void print_result(number_t result, bool is_null)
{
    if (is_null)
        printf("Результат: %s\n", "0.0");
    else
    {
        if (!strcmp("\0", result.mantissa))
            printf("Результат: %s\n", "0.0");
        else
        {
            if (result.degree >= 0)
                printf("Результат: %c0.%sE+%d\n", result.mantissa_sign, result.mantissa, result.degree);
            else
                printf("Результат: %c0.%sE%d\n", result.mantissa_sign, result.mantissa, result.degree);
        }
    }
}