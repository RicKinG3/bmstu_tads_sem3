#ifndef __CHECK_F_STR_H__
#define __CHECK_F_STR_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_empty_file(FILE *f);
bool is_normal_file(FILE *f);

bool check_int(char *num);
FILE *check_in_f(int argc, char *argv);

#endif
