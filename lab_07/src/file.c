#include "io.h"
#include "file.h"
#include "errors.h"
#include "tree.h"

#include <string.h>

void add_word_in_f(FILE *f, char *input_word)
{
    fseek(f, 0L, SEEK_END);
    fprintf(f, "\n%s", input_word);
}

int find_word_file(FILE *f, char *input_word)
{
    int rc = PASS;
    unsigned count = 0;
    char *temp_word = NULL;
    rewind(f);

    while (!rc)
    {
        temp_word = NULL;
        if (feof(f))
            break;
        rc = read_line(f, &temp_word);
        if (rc)
            break;

        if (temp_word[strlen(temp_word) - 1] == '\n')
            temp_word[strlen(temp_word) - 1] = '\0';

        if (strcmp(temp_word, input_word) == 0)
            count++;
        free(temp_word);
    }
    if (count == 0 && !rc)
    {
        rc = NOT_FIND_WORD;
    }
    else if (!rc)
        rc = count;

    return rc;
}

extern char *strdup(const char *);
#define MAX_W 1024
#include <unistd.h>

int del_word_in_file(FILE *f, char *input_word, char *name_file)
{
    int rc = PASS;
    unsigned count = 0;
    char *temp_word = NULL;
    char *file[MAX_W];
    size_t i = 0;
    while (!rc)
    {
        temp_word = NULL;
        if (feof(f))
            break;
        rc = read_line(f, &temp_word);
        if (rc)
            break;

        if (temp_word[strlen(temp_word) - 1] == '\n')
            temp_word[strlen(temp_word) - 1] = '\0';

        if (strcmp(temp_word, input_word) == 0)
        {
            count++;
        }
        else
        {
            file[i] = strdup(temp_word);

            i++;
        }
        free(temp_word);
    }
    if (count == 0 && !rc)
    {
        rc = NOT_FIND_WORD;
        return rc;
    }
    else if (!rc)
        rc = count;

    if (f == NULL)
        return 0;

    size_t j = 0;

    FILE *w = fopen(name_file, "w");

    while (i != j)
    {
        if (i == j + 1)
            fprintf(w, "%s", file[j]);
        else
            fprintf(w, "%s\n", file[j]);

        free(file[j]);
        j++;
    }
    fclose(w);
    rewind(f);

    return rc;
}

void print_file(FILE *f)
{
    int rc = PASS;
    char *temp_word = NULL;
    puts("File : ");
    while (!rc)
    {
        temp_word = NULL;
        if (feof(f))
            break;
        rc = read_line(f, &temp_word);
        if (rc)
            break;

        if (temp_word[strlen(temp_word) - 1] == '\n')
            temp_word[strlen(temp_word) - 1] = '\0';

        printf("%s ", temp_word);
        free(temp_word);
    }
}