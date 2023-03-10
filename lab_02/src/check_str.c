
#include "../inc/check_str.h"

bool check_int(char *num)
{
    for (size_t i = 1; i < strlen(num); i++)
        if (!isdigit(num[i]))
            return true;

    return false;
}

bool check_double(char *s)
{
    if (s == NULL || strlen(s) == 0 || *s == '.')
        return true;

    int count_point = 0;
    while (*s && count_point != 2)
    {
        if (*s == '.')
            count_point++;
        else if (!isdigit(*s))
            return true;
        s++;
    }
    if (count_point == 2)
        return true;
    return false;
}

bool check_name(char *name)
{
    while (*name)
    {
        if (!isalpha(*name))
            return true;
        name++;
    }
    return false;
}

bool check_group(char *group)
{
    while (*group)
    {
        if (isspace(*group))
            return true;
        group++;
    }

    return false;
}

bool check_gender(char *gender)
{
    if (*gender == 'm')
        ;
    else if (*gender == 'f')
        ;
    else
        return true;

    gender++;
    if (*gender != '\0')
        return true;
    return false;
}

bool check_type_home(inf_stdnt_t *stdnt, int pos)
{
    if (strcmp(stdnt[pos].type_home, "home") == 0)
        stdnt[pos].item_home = HOME;
    else if (strcmp(stdnt[pos].type_home, "hostel") == 0)
        stdnt[pos].item_home = HOSTEL;
    else
        return true;
    return false;
}
