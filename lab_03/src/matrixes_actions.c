#include <time.h>
#include <sys/time.h>

#include "mtres_actions.h"
#include "errors.h"

int sparse_multiply_row_and_mtr(sparse_mtr_t *row, sparse_mtr_t *mtr, int mode, int *time)
{
    if (!row->elements || !mtr->elements)
        return ERR_NO_MTR;

    int rc = MTR_OK;
    sparse_mtr_t sparse_result = {.elements = NULL, .rows = NULL, .columns = NULL, .sizes.columns = 0, .sizes.rows = 0, .sizes.nonzeros = 0};
    mtr_t result = {.mtr = NULL, .sizes.rows = 0, .sizes.columns = 0, .sizes.nonzeros = 0};

    if (row->sizes.rows != 1)
        return ERR_NONROW;

    if (row->sizes.columns != mtr->sizes.rows)
        return ERR_WRONG_mtrES_SIZES;

    rc = sparse_mtr_init(&sparse_result, 1, mtr->sizes.columns,
                         mtr->sizes.columns);

    if (rc)
        return rc;

    int nonzeros_num = 0;

    for (int begin = 0; begin < mtr->sizes.columns;) // идем по столбцам
    {
        if (mtr->columns[begin] != -1) // если столбец имеет -1 значит он нулевой и его скипаем
        {
            int sum = 0;                              // общая сумма для эл резулата вектора строки
            int end = begin + 1;                      // для конца столбца
            int begin_el_index = mtr->columns[begin]; // начала столбца не нулевой
            int end_el_index;                         // для индекса конца стоолбца
            // переход к следующему столбцу если нулевой
            while (end < mtr->sizes.columns && mtr->columns[end] == -1)
                end++;

            if (end == mtr->sizes.columns) // если последний столбец то енд = еоличеству не нулевых эл
                end_el_index = mtr->sizes.nonzeros;
            else
                end_el_index = mtr->columns[end]; // иначе полседний индекс = значению следующего столбца колума

            for (int i = begin_el_index; i < end_el_index; i++)
            {
                int el = mtr->elements[i];
                int el_row = mtr->rows[i];
                int row_el_index = row->columns[el_row];

                if (row_el_index != -1)
                    sum += el * row->elements[row_el_index];
            }

            if (sum != 0)
            {
                sparse_result.elements[nonzeros_num] = sum;
                sparse_result.rows[nonzeros_num] = 0;
                sparse_result.columns[begin] = nonzeros_num;
                nonzeros_num++;
            }

            begin = end;
        }
        else
            begin++;
    }

    sparse_result.sizes.nonzeros = nonzeros_num;

    int sizeof_mtr = sizeof(int) * mtr->sizes.nonzeros +
                     sizeof(int) * (mtr->sizes.nonzeros + mtr->sizes.columns);
    int sizeof_row = sizeof(int) * row->sizes.nonzeros +
                     sizeof(int) * (row->sizes.nonzeros + row->sizes.columns);
    int sizeof_result = sizeof(int) * nonzeros_num +
                        sizeof(int) * (nonzeros_num + sparse_result.sizes.columns);
    int mem_result = sizeof_mtr + sizeof_result + sizeof_row;

    *time = mem_result;

    rc = mtr_init(&result, 1, mtr->sizes.columns, nonzeros_num);

    if (rc)
    {
        free_sparse_t(&sparse_result);
        return rc;
    }

    create_mtr_by_sparse(&sparse_result, &result);
    if (mode)
        rc = choice_print(&result, &sparse_result);

    free_mtr_t(&result);
    free_sparse_t(&sparse_result);

    return rc;
}

int multiply_row_and_mtr(mtr_t *row, mtr_t *mtr, int mode, int *time)
{
    if (!row->mtr || !mtr->mtr)
        return ERR_NO_MTR;

    int rc = MTR_OK;
    mtr_t result = {.mtr = NULL, .sizes.rows = 0, .sizes.columns = 0, .sizes.nonzeros = 0};
    sparse_mtr_t sparse_result;

    if (row->sizes.rows != 1)
        return ERR_NONROW;

    if (row->sizes.columns != mtr->sizes.rows)
        return ERR_WRONG_mtrES_SIZES;

    rc = mtr_init(&result, 1, mtr->sizes.columns, mtr->sizes.rows);

    if (rc)
        return rc;

    rc = sparse_mtr_init(&sparse_result, 1, mtr->sizes.rows,
                         mtr->sizes.rows);

    if (rc)
    {
        free_mtr_t(&result);
        return rc;
    }

    for (int i = 0; i < row->sizes.columns; i++)
    {
        result.mtr[0][i] = 0;

        for (int j = 0; j < row->sizes.columns; j++)
            result.mtr[0][i] += row->mtr[0][j] * mtr->mtr[j][i];
    }

    int sizeof_mtr = sizeof(int) * mtr->sizes.rows * mtr->sizes.columns;
    int sizeof_row = sizeof(int) * row->sizes.rows * row->sizes.columns;
    int sizeof_result = sizeof(int) * row->sizes.rows * mtr->sizes.columns;
    int mem_result = sizeof_mtr + sizeof_result + sizeof_row;

    *time = mem_result;

    create_sparse_by_mtr(&result, &sparse_result);
    if (mode)
        rc = choice_print(&result, &sparse_result);

    free_mtr_t(&result);
    free_sparse_t(&sparse_result);

    return rc;
}

int choice_print(mtr_t *mtr, sparse_mtr_t *sparse_mtr)
{
    int rc = MTR_OK;
    int choice;

    puts("Выберете формат вывода результирующией матрицы:");
    puts("    0 - стандартный;");
    puts("    1 - разреженный.");

    rc = read_int(&choice);
    clear_stdin();

    if (rc || (choice != 0 && choice != 1))
        return ERR_PRINT_FLAG_READ;

    puts("\nРезультат умножения вектора-строки на матрицу:\n");

    if (choice)
        rc = print_sparse(sparse_mtr);
    else
        rc = print_mtr(mtr);

    return rc;
}

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

void print_table_measure(sparse_mtr_t *row, sparse_mtr_t *mtr, mtr_t *rw, mtr_t *mr)
{
    puts("");
    long long time = 0, ttime = 0;
    long long unsigned beg, end;
    int mem = 0;
    int memt = 0;
    beg = milliseconds_now();
    for (int i = 0; i < 1000; i++)
        sparse_multiply_row_and_mtr(row, mtr, MODE_NOT_PRINT, &mem);
    end = milliseconds_now();
    time = end - beg;

    beg = milliseconds_now();
    for (int i = 0; i < 1000; i++)
        multiply_row_and_mtr(rw, mr, MODE_NOT_PRINT, &memt);
    end = milliseconds_now();
    ttime = end - beg;

    printf("|    | %-15s | %-15s |\n", "sparse multiply", "multiply");
    printf("|----------------------------------------|\n");
    printf("| mc | %-15llu | %-15llu |\n", time, ttime);
    printf("| bt | %-15d | %-15d |\n\n", mem, memt);
}