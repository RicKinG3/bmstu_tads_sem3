
#include "check_str.h"

bool check_int(char *num)
{
    for (size_t i = 1; i < strlen(num); i++)
        if (!isdigit(num[i]))
            return true;

    return false;
}
