#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "mtr.h"
#include "errors.h"
#include "func.h"

#define MAX_PRINT_SIZE 30

void free_mtr_t(mtr_t *mtr)
{
    free_mtr(mtr->mtr, mtr->sizes.rows);
    mtr->mtr = NULL;
    mtr->sizes.rows = 0;
    mtr->sizes.columns = 0;
    mtr->sizes.nonzeros = 0;
}

void free_sparse_t(sparse_mtr_t *sparse_mtr)
{
    free(sparse_mtr->elements);
    free(sparse_mtr->rows);
    free(sparse_mtr->columns);
    sparse_mtr->elements = NULL;
    sparse_mtr->rows = NULL;
    sparse_mtr->columns = NULL;
    sparse_mtr->sizes.columns = 0;
    sparse_mtr->sizes.rows = 0;
    sparse_mtr->sizes.nonzeros = 0;
}

int mtr_init(mtr_t *mtr, int rows, int columns, int nonzero_num)
{
    mtr->sizes.rows = rows;
    mtr->sizes.columns = columns;
    mtr->sizes.nonzeros = nonzero_num;

    mtr->mtr = allocate_mtr(rows, columns);

    if (mtr->mtr == NULL)
        return ERR_MEMORY_ALLOCATION;

    return MTR_OK;
}

int **allocate_mtr(int n, int m)
{
    int **data = calloc(n, sizeof(int *));

    if (!data)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        data[i] = calloc(m, sizeof(int));
        if (!data[i])
        {
            free_mtr(data, n);
            return NULL;
        }
    }
    return data;
}

void free_mtr(int **data, int n)
{
    for (int i = 0; i < n; i++)
        free(data[i]);

    free(data);
}

int sparse_mtr_init(sparse_mtr_t *mtr, int rows, int columns, int nonzero_num)
{
    mtr->sizes.rows = rows;
    mtr->sizes.columns = columns;
    mtr->sizes.nonzeros = nonzero_num;

    mtr->elements = calloc(nonzero_num, sizeof(int));

    if (!mtr->elements)
        return ERR_MEMORY_ALLOCATION;

    mtr->rows = calloc(nonzero_num, sizeof(int));

    if (!mtr->rows)
        return ERR_MEMORY_ALLOCATION;

    mtr->columns = malloc(columns * sizeof(int));

    if (!mtr->columns)
        return ERR_MEMORY_ALLOCATION;

    for (int i = 0; i < columns; i++)
        mtr->columns[i] = -1;

    return MTR_OK;
}

size_t read_line(char *s, size_t n, FILE *f)
{
    int ch;
    size_t i = 0;
    while ((ch = fgetc(f)) != '\n' && ch != EOF)
        if (i < n - 1)
            s[i++] = ch;
    s[i] = '\0';
    if (i == 0 || s[0] == '\n')
        return ERR_STR_READ;
    return PASS;
}

int read_mtres(sparse_mtr_t *sparse_mtr, sparse_mtr_t *sparse_row,
               mtr_t *mtr, mtr_t *row)
{
    int rc = MTR_OK;
    int rows_num = 0, columns_num = 0;

    rc = read_mtr(mtr, sparse_mtr, &rows_num, &columns_num);

    if (rc)
        return rc;

    rc = read_row(row, sparse_row, rows_num);

    return rc;
}

int read_mtr(mtr_t *mtr, sparse_mtr_t *sparse_mtr,
             int *rows_num, int *columns_num)
{
    int rc = MTR_OK;
    int nonzero_num = 0;

    puts("Введите кол-во строк матрицы: ");

    rc = read_int(rows_num);
    clear_stdin();

    if (rc || !rows_num)
        return rc;

    puts("Введите кол-во столбцов матрицы: ");

    rc = read_int(columns_num);
    clear_stdin();

    if (rc || !columns_num)
        return rc;

    printf("Введите кол-во ненулевых элементов матрицы (максимально = %d):\n",
           *rows_num * *columns_num);

    rc = read_int(&nonzero_num);
    clear_stdin();

    if (rc)
        return rc;

    if (nonzero_num > *rows_num * *columns_num)
        return ERR_TOO_MUCH_NONZERO;

    free_mtr_t(mtr);
    free_sparse_t(sparse_mtr);

    rc = mtr_init(mtr, *rows_num, *columns_num, nonzero_num);

    if (rc)
        return rc;

    rc = sparse_mtr_init(sparse_mtr, *rows_num, *columns_num, nonzero_num);

    if (rc)
    {
        free_mtr(mtr->mtr, mtr->sizes.rows);
        return rc;
    }

    if (nonzero_num)
    {
        printf("Введите %d элемент(а/ов) матрицы в формате \"строка столбец значение\""
               "(без ковычек):\n",
               nonzero_num);

        rc = read_mtr_elements(sparse_mtr, mtr, nonzero_num);
        clear_stdin();
    }

    if (rc)
    {
        free_mtr_t(mtr);
        free_sparse_t(sparse_mtr);
    }

    return rc;
}

int read_row(mtr_t *row, sparse_mtr_t *sparse_row, int columns_num)
{
    int rc = MTR_OK;
    int nonzero_num = 0;

    printf("Введите кол-во ненулевых элементов вектора-строки (максимум = %d):\n",
           columns_num);

    read_int(&nonzero_num);
    clear_stdin();

    if (rc)
        return rc;

    if (nonzero_num > columns_num)
        return ERR_TOO_MUCH_NONZERO;

    free_mtr_t(row);
    free_sparse_t(sparse_row);

    rc = mtr_init(row, 1, columns_num, nonzero_num);

    if (rc)
        return rc;

    rc = sparse_mtr_init(sparse_row, 1, columns_num, nonzero_num);

    if (rc)
    {
        free_mtr_t(row);
        return rc;
    }

    if (nonzero_num)
    {
        printf("Введите %d элемент(а/ов) вектора-строки в формате \"столбец значение\""
               "(без ковычек):\n",
               nonzero_num);

        rc = read_row_elements(sparse_row, row, nonzero_num);
        clear_stdin();
    }

    if (rc)
    {
        free_mtr_t(row);
        free_sparse_t(sparse_row);
    }

    return rc;
}

int read_mtr_elements(sparse_mtr_t *sparse_mtr, mtr_t *mtr,
                      int nonzeros)
{
    int rc = MTR_OK;

    for (int i = 0; i < nonzeros; i++)
    {
        int row;
        int column;
        int num;

        rc = read_int(&row);

        if (rc || row >= sparse_mtr->sizes.rows || row >= mtr->sizes.rows)
            return ERR_WRONG_ELEMENT_PARAMETERS;

        rc = read_int(&column);

        if (rc || column >= sparse_mtr->sizes.columns || column >= mtr->sizes.columns)
            return ERR_WRONG_ELEMENT_PARAMETERS;

        if (scanf("%d", &num) != 1)
            return ERR_NONINTEGER;

        mtr->mtr[row][column] = num;
    }

    create_sparse_by_mtr(mtr, sparse_mtr);

    return MTR_OK;
}

int read_row_elements(sparse_mtr_t *sparse_row, mtr_t *row,
                      int nonzeros)
{
    int rc = MTR_OK;

    for (int i = 0; i < nonzeros; i++)
    {
        int column;
        int num;

        rc = read_int(&column);

        if (rc || column >= sparse_row->sizes.columns || column >= row->sizes.columns)
            return ERR_WRONG_ELEMENT_PARAMETERS;

        if (scanf("%d", &num) != 1)
            return ERR_NONINTEGER;

        row->mtr[0][column] = num;
    }

    create_sparse_by_mtr(row, sparse_row);

    return MTR_OK;
}

void create_sparse_by_mtr(mtr_t *mtr, sparse_mtr_t *sparse_mtr)
{
    int count = 0;

    for (int j = 0; j < mtr->sizes.columns; j++)
    {
        for (int i = 0; i < mtr->sizes.rows; i++)
        {
            int element = mtr->mtr[i][j];

            if (element)
            {

                sparse_mtr->elements[count] = element;
                sparse_mtr->rows[count] = i;

                if (sparse_mtr->columns[j] == -1)
                    sparse_mtr->columns[j] = count;

                count++;
            }
        }
    }

    sparse_mtr->sizes.nonzeros = count;
    sparse_mtr->sizes.rows = mtr->sizes.rows;
    sparse_mtr->sizes.columns = mtr->sizes.columns;
}

void create_mtr_by_sparse(sparse_mtr_t *sparse_mtr, mtr_t *mtr)
{
    for (int begin = 0; begin < sparse_mtr->sizes.columns;)
    {
        if (sparse_mtr->columns[begin] != -1)
        {
            // el -- element
            int end = begin + 1;
            int begin_el_index = sparse_mtr->columns[begin];
            int end_el_index;

            while (end < sparse_mtr->sizes.columns &&
                   sparse_mtr->columns[end] == -1)
                end++;

            if (end == mtr->sizes.columns)
                end_el_index = sparse_mtr->sizes.nonzeros;
            else
                end_el_index = sparse_mtr->columns[end];

            for (int i = begin_el_index; i < end_el_index; i++)
            {
                int el = sparse_mtr->elements[i];
                int el_row = sparse_mtr->rows[i];

                mtr->mtr[el_row][begin] = el;
            }

            begin = end;
        }
        else
            begin++;
    }
}

int user_print(mtr_t *mtr, mtr_t *row,
               sparse_mtr_t *sparse_mtr, sparse_mtr_t *sparse_row)
{
    int rc = MTR_OK;
    int choice;

    if (!mtr->mtr || !row->mtr)
        return ERR_NO_MTR;

    puts("Для выбора формата вывода матриц введите 0 либо 1:");
    puts("    0 - стандартный;");
    puts("    1 - разреженный.");

    rc = read_int(&choice);
    clear_stdin();

    if (rc || (choice != 0 && choice != 1))
        return ERR_PRINT_FLAG_READ;

    if (choice)
    {
        puts("\nИсходная матрица:");
        rc = print_sparse(sparse_mtr);

        if (rc)
            return rc;

        puts("\nИсходный вектор-строка:");
        rc = print_sparse(sparse_row);

        if (rc)
            return rc;
    }
    else
    {
        puts("\nИсходная матрица:");
        rc = print_mtr(mtr);

        if (rc)
            return rc;

        puts("\nИсходный вектор-строка:");
        rc = print_mtr(row);

        if (rc)
            return rc;
    }

    return MTR_OK;
}

int print_mtr(mtr_t *mtr)
{
    int rc = MTR_OK;
    int print_flag = 1;

    if (mtr->sizes.rows > MAX_PRINT_SIZE ||
        mtr->sizes.columns > MAX_PRINT_SIZE)
    {
        printf("\nОдна из размерностей выводимой матрицы больше %d!\n",
               MAX_PRINT_SIZE);
        puts("Вывести матрицу? (0 - нет, 1 - да)");

        rc = read_int(&print_flag);
        clear_stdin();

        if (rc || (print_flag != 0 && print_flag != 1))
            return ERR_PRINT_FLAG_READ;
    }

    if (print_flag)
    {
        for (int i = 0; i < mtr->sizes.rows; i++)
        {
            for (int j = 0; j < mtr->sizes.columns; j++)
                printf("%6d ", mtr->mtr[i][j]);

            puts("");
        }
    }

    return MTR_OK;
}

int print_sparse(sparse_mtr_t *mtr)
{
    int rc = MTR_OK;
    int print_flag = 1;

    if (mtr->sizes.rows > MAX_PRINT_SIZE ||
        mtr->sizes.columns > MAX_PRINT_SIZE ||
        mtr->sizes.nonzeros > MAX_PRINT_SIZE)
    {
        printf("\nОдна из размерностей выводимой матрицы больше %d!\n",
               MAX_PRINT_SIZE);
        puts("Вывести матрицу? (0 - нет, 1 - да)");

        rc = read_int(&print_flag);
        clear_stdin();

        if (rc || (print_flag != 0 && print_flag != 1))
            return ERR_PRINT_FLAG_READ;
    }

    if (print_flag)
    {
        puts("\nЗначения элементов:");
        for (int i = 0; i < mtr->sizes.nonzeros; i++)
            printf("%6d ", mtr->elements[i]);
        puts("");

        puts("\nИндекс строк этих элементов:");
        for (int i = 0; i < mtr->sizes.nonzeros; i++)
            printf("%6d ", mtr->rows[i]);
        puts("");

        puts("\nИндекс элемента, с которого начинается j-ый столбец:");
        for (int i = 0; i < mtr->sizes.columns; i++)
            printf("%6d ", mtr->columns[i]);
        puts("");
    }

    puts("\n-1 в означает, что в столбце нет элементов");

    return MTR_OK;
}

int generate_mtres(sparse_mtr_t *sparse_mtr, sparse_mtr_t *sparse_row,
                   mtr_t *mtr, mtr_t *row)
{
    puts("\nРазмеры вектора-строки задаются таким же размером как у матрицы размер строк  для возможности умножения.");
    puts("Процент заполенности такой же, как у матрицы\n");

    int rc = MTR_OK;
    int percent = 0;
    int rows_num, columns_num;

    puts("Введите кол-во строк матрицы: ");

    rc = read_int(&rows_num);
    clear_stdin();

    if (rc || !rows_num)
        return rc;

    puts("Введите кол-во столбцов матрицы: ");

    rc = read_int(&columns_num);
    clear_stdin();

    if (rc || !columns_num)
        return rc;

    puts("Введите процент заполненности матрицы: ");

    rc = read_int(&percent);
    clear_stdin();

    if (rc)
        return rc;

    if (percent < 0 || percent > 100)
        return ERR_WRONG_PERCENT;

    int non_zeros = my_round(((double)rows_num * columns_num * percent) / 100);

    if (!non_zeros)
        return ERR_EMPTY_MTR;

    free_mtr_t(mtr);
    free_mtr_t(row);
    free_sparse_t(sparse_mtr);
    free_sparse_t(sparse_row);

    rc = mtr_init(mtr, rows_num, columns_num, non_zeros);

    if (rc)
        return rc;

    rc = sparse_mtr_init(sparse_mtr, rows_num, columns_num, non_zeros);

    if (rc)
    {
        free_mtr_t(mtr);
        return rc;
    }

    generate_mtr(mtr, sparse_mtr);

    non_zeros = my_round(((double)rows_num * percent) / 100);
    if (!non_zeros)
    {
        free_mtr_t(mtr);
        free_sparse_t(sparse_mtr);
        return ERR_EMPTY_MTR;
    }

    rc = mtr_init(row, 1, rows_num, non_zeros);

    if (rc)
    {
        free_mtr_t(mtr);
        free_sparse_t(sparse_mtr);
        return rc;
    }

    rc = sparse_mtr_init(sparse_row, 1, rows_num, non_zeros);

    if (rc)
    {
        free_mtr_t(mtr);
        free_mtr_t(row);
        free_sparse_t(sparse_mtr);
        return rc;
    }

    generate_mtr(row, sparse_row);
    return rc;
}

void generate_mtr(mtr_t *mtr, sparse_mtr_t *sparse_mtr)
{
    srand(time(NULL));

    for (int i = 0, ii = 0, jj = 0; i < mtr->sizes.nonzeros;)
    {
        ii = rand() % mtr->sizes.rows;
        jj = rand() % mtr->sizes.columns;
        int el = -50 + rand() % 101;

        if (fabs(*(*(mtr->mtr + ii) + jj)) <= EPS && el != 0)
        {
            *(*(mtr->mtr + ii) + jj) = el;
            i++;
        }
    }

    create_sparse_by_mtr(mtr, sparse_mtr);
}