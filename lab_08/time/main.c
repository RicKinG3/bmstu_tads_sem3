#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int args, char **argv)
{
    FILE *f = fopen("../data/1.txt", "w+");
    if (args == 2)
    {
        int num = atoi(argv[1]);
        if (num != 0)
        {

            fprintf(f, "%d\n", num);
            size_t i = 0;
            for (; i < num - 1; i++)
            {
               
                fprintf(f, "%ld %ld\n", i, i + 1);
            }
            fprintf(f, "%d %ld", 0, i);
            fclose(f);
        }
    }
}