#ifndef _README_H_

#define _README_H_

#define PASS 0
#define ERR_INPUT 1
#define DATA_ERROR 2

#define LEN 30
#define P 5

typedef struct
{
    char number[LEN];
    short int len;
    char sign;
    // for real
    short int after_dot_len;
    int order;
} number;

#include <stdbool.h>
bool is_e(char ch);
bool is_strend(char ch);
size_t put_num_in_struct(number *numstruct, char *strnum);

int is_null(char *s, int pos);
bool is_dot(char ch);
bool is_space(char ch);
int read_flt(number *number_flt, char *);
int read_int(number *, char *);

bool is_sign(char ch);

#endif