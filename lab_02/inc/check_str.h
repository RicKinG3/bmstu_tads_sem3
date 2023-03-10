#ifndef __CHECK_STR_H__
#define __CHECK_STR_H__

#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "../inc/struct_inf_stdnt.h"

bool check_int(char *num);
bool check_double(char *s);
bool check_name(char *name);
bool check_group(char *group);
bool check_gender(char *gender);
bool check_type_home(inf_stdnt_t *stdnt, int pos);

#endif