#ifndef __func_H__

#define __func_H__

#include <stdlib.h>
#include <stdio.h>

#define READ_OK 0
#define ERR_FGETS -1
#define ERR_STR_READ -2

size_t my_strlen(char *str);
void clear_stdin(void);
int read_int(int *integer);
int my_round(double number);
int read_str(char *str, int max_len, FILE *stream);

#endif
